/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/07 11:37:28 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	read_input(t_minishell *ms)
{
	t_lexer	lex;

	lex.token_list = NULL;
	lex.input = NULL;
	lex.envp = ms->envp;
	lex.input = readline("./minishell ");
	if (lex.input == NULL)
		return (1);
	lex.i = 0;
	if (ft_strncmp(lex.input, "exit", 4) == 0)
		exit (0);
	if (lex_input(&lex) == 1)
		return (1);
	printf("Before expansion: \n");
	ft_putlst_fd(lex.token_list, 1);
	if (check_for_expansion(&lex.token_list, ms->envp) == 1)
		return (1);
	printf("After expansion: \n");
	ft_putlst_fd(lex.token_list, 1);
	printf("Before dequotation: \n");
	if (check_for_dequotation(&lex.token_list) == 1)
		return (1);
	printf("After dequotation: \n");
	ft_putlst_fd(lex.token_list, 1);
	return (ft_lstclear(&lex.token_list), 0);
}

int	lex_input(t_lexer *lex)
{
	t_list	*new_token;

	while (lex->input[lex->i] != '\0')
	{
		while (ft_isspace(lex->input[lex->i]) == true)
			lex->i++;
		if (lex->input[lex->i] == '\0')
			break ;
		if (is_token(lex->input[lex->i]) == true)
			new_token = get_non_word_token(lex);
		else
			new_token = get_word_token(lex);
		if (new_token == NULL)
		{
			if (lex->token_list != NULL)
				ft_lstclear(&lex->token_list);
			return (ft_putendl_fd("Error: Malloc Error", 2), 1);
		}
		ft_lstadd_back(&lex->token_list, new_token);
	}
	return (0);
}

bool	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

t_list	*get_word_token(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	int		len;

	attr = NULL;
	len = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
		{
			if (handle_quotes(lex, lex->input[lex->i], &len) == 1)
				return (NULL);
		}
		if (ft_isspace(lex->input[lex->i]) == true
			|| is_token(lex->input[lex->i]) == true)
			break ;
		lex->i++;
		len++;
	}
	attr = (char *)malloc((len + 1) * sizeof(char));
	if (attr == NULL)
		return (NULL);
	ft_strlcpy(attr, lex->input + (lex->i - len), len + 1);
	new_token = ft_lstnew(WORD, attr);
	return (new_token);
}

t_list	*get_non_word_token(t_lexer *lex)
{
	t_list	*new_token;

	new_token = NULL;
	if (lex->input[lex->i] == '|')
		new_token = ft_lstnew(PIPE, NULL);
	else if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] != '<')
		new_token = ft_lstnew(RE_IN, NULL);
	else if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] != '>')
		new_token = ft_lstnew(RE_OUT, NULL);
	else if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] == '<')
	{
		new_token = ft_lstnew(HERE_DOC, NULL);
		lex->i++;
	}
	else if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] == '>')
	{
		new_token = ft_lstnew(APPEND, NULL);
		lex->i++;
	}
	lex->i++;
	return (new_token);
}

int	handle_quotes(t_lexer *lex, char quote, int *len)
{
	bool	is_closed;
	

	is_closed = false;
	lex->i++;
	*len += 1;
	while (lex->input[lex->i] != '\0')
	{
		if (lex->input[lex->i] == quote)
		{
			is_closed = true;
			break ;
		}
		lex->i++;
		*len += 1;
	}
	if (is_closed == false)
		return (1);
	return (0);
}

int	check_for_dequotation(t_list **token_list)
{
	t_list	*current_node;

	current_node = *token_list;
	while (current_node != NULL)
	{
		if (current_node->type == 1)
		{
			if (ft_strchr(current_node->attr, '"') != NULL || ft_strchr(current_node->attr, '\'') != NULL)
			{
				current_node->attr = handle_dequotation(current_node->attr, 0, 0);
				if (current_node->attr == NULL)
					return (1);
			}
		}
		current_node = current_node->next;
	}
	return (0);
}

char	*handle_dequotation(char *to_trim, int i, int j)
{
	char	*trim_str;
	char	quote;

	trim_str = (char *)malloc((get_dequoted_strlen(to_trim) + 1) * (sizeof(char)));
	if (trim_str == NULL)
		return (NULL);
	while (to_trim[i] != '\0')
	{
		if (to_trim[i] == '\'' || to_trim[i] == '"')
		{
			quote = to_trim[i++];
			while (to_trim[i] != quote)
				trim_str[j++] = to_trim[i++];
			i++;
		}
		else
			trim_str[j++] = to_trim[i++];
	}
	trim_str[j] = '\0';
	return (free(to_trim), trim_str);
}

int	get_dequoted_strlen(char *str)
{
	char	quote;
	int		num_of_quotes;
	int		i;
	
	num_of_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			num_of_quotes++;
			quote = str[i++];
			while (str[i] != '\0')
			{
				if (str[i] == quote)
				{
					num_of_quotes++;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (ft_strlen(str) - num_of_quotes);
}

int	check_for_expansion(t_list **token_list, char **envp)
{
	t_list	*current_node;
	int		i;

	current_node = *token_list;
	while (current_node != NULL)
	{
		if (current_node->type == 1)
		{
			i = 0;
			while (current_node->attr[i] != '\0')
			{
				if (current_node->attr[i] == '$')
				{
					current_node->attr = handle_expansion(current_node->attr, envp, &i);
					if (current_node->attr == NULL)
						return (1);
					continue;
				}
				if (current_node->attr[i] == '\'' && current_node->in_squotes == false)
					current_node->in_squotes = true;
				else
					current_node->in_squotes = false;
				i++;
			}
		}
		current_node = current_node->next;
	}
	return (0);
}

char	*handle_expansion(char *to_expand, char **envp, int *i)
{
	int		len;
	int		pos;
	int		j;
	//int		quote;
	
	if (ft_isspace(to_expand[*i + 1]) == true || to_expand[*i + 1] == '\0'
		|| to_expand[*i + 1] == '\'' || to_expand[*i + 1] == '"'
		|| to_expand[*i + 1] == '?')
		return (*i = *i + 1, to_expand);
	pos = *i + 1;
	len = 0;
	while (to_expand[*i] != '\0' && ft_isspace(to_expand[*i]) == false
		&& to_expand[*i] != '\'' && to_expand[*i] != '"')
	{
		*i = *i + 1;
		len++;
	}
	// quote = 0;
	// if (to_expand[*i] == '\'' || to_expand[*i] == '"')
	// 	quote = 1;
	// printf("%s\n", to_expand + pos);
	// printf("To read chars: %d\n", len - 1);// - quote);
	j = -1;
	while (envp[++j] != NULL)
	{
		//if (ft_strnstr(envp[j], to_expand + pos, len - 1) != NULL) //&& envp[j][len - 1] == '=')
		if (ft_strncmp(envp[j], to_expand + pos, len - 1) == 0)
		{
			// printf("%s\n", "Found");
			return (*i = 0, handle_valid_expansion(to_expand, envp[j], len, pos));
		}
	}
	// printf("Never found\n");
	return (*i = 0, handle_invalid_expansion(to_expand, len));
}

char	*handle_valid_expansion(char *to_expand, char *env, int len, int pos)
{
	char	*exp_str;
	char	*exp_var;
	int		i;
	int		j;
	
	// ft_putendl_fd(env, 1);
	// ft_putendl_fd(env + len, 1);
	exp_var = ft_substr(env, len, ft_strlen(env) - len);
	if (exp_var == NULL)
		return (NULL);
	// printf("LEN: %d\n", len);
	// ft_putendl_fd(exp_var, 1);
	exp_str = (char *)malloc(((ft_strlen(to_expand) - len + ft_strlen(exp_var) + 1) * sizeof(char)));
	if (exp_str == NULL)
		return (free(exp_var), NULL);
	i = 0;
	j = 0;
	while (to_expand[j] != '\0' && to_expand[j] != '$')
		exp_str[i++] = to_expand[j++];
	j = 0;
	while (exp_var[j] != '\0')
		exp_str[i++] = exp_var[j++];
	j = pos + len - 1;
	while (to_expand[j] != '\0')
		exp_str[i++] = to_expand[j++];
	exp_str[i] = '\0';
	// ft_putendl_fd(exp_str, 1);
	return (free(to_expand), free(exp_var), exp_str);
}

char	*handle_invalid_expansion(char *str, int len)
{
	char	*new_str;
	int		i;

	//printf("New size should be: 13 and is actually %lu\n", ft_strlen(str) - len);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	ft_strlcpy(new_str, str, i + 1);
	ft_strlcat(new_str + i, str + i + len, ft_strlen(str) - len - i + 1);
	free(str);
	return (new_str);	
}

size_t	ft_strlen_except(const char *str, char *exceptions)
{
	size_t	len;
	bool	is_except;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		is_except = false;
		j = 0;
		while (exceptions[j] != '\0')
		{
			if (str[i] == exceptions[j])
				is_except = true;
			j++;
		}
		if (is_except == false)
			len++;
		i++;
	}
	return (len);
}

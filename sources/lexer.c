/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/06 09:36:45 by shaintha         ###   ########.fr       */
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
	if (lex_input(&lex) == 1)
		return (1);
	printf("Before expansion: \n");
	ft_putlst_fd(lex.token_list, 1);
	check_for_expansion(&lex.token_list, ms->envp);
	printf("After expansion: \n");
	ft_putlst_fd(lex.token_list, 1);
	ft_lstclear(&lex.token_list);
	return (0);
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


int	check_for_quotes(t_list **token_list)
{
	t_list	*current_node;
	int		i;

	current_node = *token_list;
	if (token_list == NULL)
		return (1);
	while (current_node != NULL)
	{
		if (current_node->type == 1)
		{
			i = 0;
			while (current_node->attr[i] != '\0')
			{
				if (current_node->attr[i] == '"' || current_node->attr[i] == '\'')
				{
					//current_node->attr;
					if (current_node->attr == NULL)
						return (1);
					ft_putendl_fd(current_node->attr, 1);
					continue;
				}
				i++;
			}
		}
		current_node = current_node->next;
	}
	return (0);
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
				if (current_node->attr[i] == '\'' && current_node->in_squotes == false)
					current_node->in_squotes = true;
				else
					current_node->in_squotes = false;
				if (current_node->attr[i] == '$' && current_node->in_squotes == false)
				{
					current_node->attr = handle_expansion(current_node->attr, envp, &i);
					if (current_node->attr == NULL)
						return (1);
					ft_putendl_fd(current_node->attr, 1);
					continue;
				}
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
	int		j;
	
	
	printf("First c: %c and pos: %d\n", to_expand[*i], *i);
	if (ft_isspace(to_expand[*i + 1]) == true || to_expand[*i + 1] == '\0')
		return (*i = *i + 1, to_expand);
	len = 0;
	while (to_expand[*i] != '\0' && ft_isspace(to_expand[*i]) == false)
	{
		*i = *i + 1;
		len++;
	}
	j = 0;
	printf("Total strlen= %zu, str_pos= %i, env_len= %i\n", ft_strlen(to_expand), *i, len);
	while (envp[j] != NULL)
	{
		if (ft_strnstr(envp[j], to_expand + 1, len - 1) == NULL)
			j++;
		else
		{
			*i = 0;
			return (handle_valid_expansion(to_expand, envp[j], len));
		}
	}
	*i = 0;
	return (handle_invalid_expansion(to_expand, len));
}

char	*handle_valid_expansion(char *to_expand, char *env, int len)
{
	char	*exp_var;
	
	ft_putendl_fd(env, 1);
	exp_var = ft_substr(env, len, ft_strlen(env) - ft_strlen(to_expand));
	if (exp_var == NULL)
		return (NULL);
	ft_putendl_fd(exp_var, 1);
	return (exp_var);
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
	//printf("New size should be: 13 and is actually %lu\n", ft_strlen(new_str));
	free(str);
	return (new_str);	
}


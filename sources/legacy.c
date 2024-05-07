/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/07 13:52:03 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_type	get_redir_type(t_lexer *lex)
{
	t_type	type;

	if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] != '<')
		type = RE_IN;
	if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] != '>')
		type = RE_OUT;
	lex->i++;
	if (lex->input[lex->i] == '<' && lex->input[lex->i - 1] == '<')
	{
		type = HERE_DOC;
		lex->i++;
	}
	if (lex->input[lex->i] == '>' && lex->input[lex->i - 1] == '>')
	{
		type = APPEND;
		lex->i++;
	}
	return (type);
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

// t_list	*get_redir_token_old(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	t_type	type;
// 	char	*attr;
// 	int		j;

// 	type = get_redir_type(lex);
// 	while (ft_isspace(lex->input[lex->i]) == true)
// 		lex->i++;
// 	if (lex->input[lex->i] == '\0')
// 		return (NULL);
// 	j = 0;
// 	while (lex->input[lex->i] != '\0')
// 	{
// 		if (ft_isspace(lex->input[lex->i]) == true || lex->input[lex->i] == '<' 
// 			|| lex->input[lex->i] == '>' || lex->input[lex->i] == '|')
// 			break ;
// 		lex->i++;
// 		j++;
// 	}
// 	attr = (char *)malloc((j + 1) * sizeof(char));
// 	if (attr == NULL)
// 		return (NULL);
// 	ft_strlcpy(attr, lex->input + (lex->i - j), j + 1);
// 	new_token = ft_lstnew(type, attr);
// 	return (new_token);
// }

// int	lex_input_old(t_lexer *lex)
// {
// 	t_list	*new_token;

// 	while (lex->input[lex->i] != '\0')
// 	{
// 		while (ft_isspace(lex->input[lex->i]) == true)
// 			lex->i++;
// 		if (lex->input[lex->i] == '|')
// 		{	
// 			new_token = ft_lstnew(PIPE, "|");
// 			lex->i++;
// 		}
// 		else if (lex->input[lex->i] == '<' || lex->input[lex->i] == '>')		
// 			new_token = get_redir_token(lex);
// 		else 
// 			new_token = get_word_token(lex);
// 		if (new_token == NULL)
// 		{
// 			if (lex->token_list != NULL)
// 				ft_lstclear(&lex->token_list);
// 			return (1);
// 		}
// 		ft_lstadd_back(&lex->token_list, new_token);
// 	}
// 	return (0);
// }

// void	expand_env(t_lexer *lex, t_list **lst)
// {
// 	t_list	*temp;

// 	temp = *lst;
// 	if (lst == NULL)
// 		return ;
// 	while (temp != NULL)
// 	{
// 		if (temp->type == 1 && ft_strchr(temp->attr, '$'))
// 			temp->attr = handle_expansion(lex, temp->attr);
// 		temp = temp->next;
// 	}
// }

// t_list	*handle_quotes(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	char	*attr;
// 	char	quote;
// 	bool	is_closed;
// 	int		len;

// 	if (lex->input[lex->i] == '\"')
// 		quote = '\"';
// 	else
// 		quote = '\'';
// 	is_closed = false;
// 	lex->i++;
// 	len = 1;
// 	while (lex->input[lex->i] != '\0')
// 	{
// 		if (lex->input[lex->i] == quote)
// 			is_closed = true;
// 		lex->i++;
// 		len++;
// 	}
// 	// if (is_closed == false)
// 	// 	return (NULL);
// 	attr = (char *)malloc((len + 2) * sizeof(char));
// 	if (attr == NULL)
// 		return (NULL);
// 	ft_strlcpy(attr, lex->input + (lex->i - 1 - len), len + 2);
// 	new_token = ft_lstnew(WORD, attr);
// 	return (new_token);
// }

// t_list	*get_word_token2(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	char	*attr;
// 	int		len;

// 	attr = NULL;
// 	len = 0;
// 	while (lex->input[lex->i] != '\0')
// 	{
// 		// if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
// 		// 	return (handle_quotes(lex));
// 		if (ft_isspace(lex->input[lex->i]) == true
// 			|| is_token(lex->input[lex->i]) == true)
// 			//|| lex->input[lex->i] == '"' || lex->input[lex->i] == '\'')
// 			break ;
// 		if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
// 			return (handle_quotes(lex));
// 		lex->i++;
// 		len++;
// 	}
// 	attr = (char *)malloc((len + 1) * sizeof(char));
// 	if (attr == NULL)
// 		return (NULL);
// 	ft_strlcpy(attr, lex->input + (lex->i - len), len + 1);
// 	new_token = ft_lstnew(WORD, attr);
// 	return (new_token);
// }
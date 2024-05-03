/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/03 15:37:25 by shaintha         ###   ########.fr       */
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
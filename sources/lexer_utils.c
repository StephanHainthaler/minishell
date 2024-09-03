/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:15:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/03 12:16:12 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Checks for the pre-defined tokens.
//<PARAM> The character to be checked.
//<RETURN> bool
bool	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

//Gets a single word token and stores it in a new node.
//If improper quotation closure has been detected, 
//returning NULL will be considered a standard ERROR.
//<PARAM> The lexer struct & the checker for quotation errors.
//<RETURN> The node on SUCCES; NULL on FATAL ERROR
t_list	*get_word_token(t_lexer *lex, int *error)
{
	t_list	*new_token;
	char	*attr;
	size_t	len;

	attr = NULL;
	len = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
		{
			if (handle_quote_closure(lex, lex->input[lex->i], &len) == 1)
				return (*error = 1, NULL);
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

//Gets a single non-word token and stores it in a new node.
//<PARAM> The lexer struct.
//<RETURN> The node on SUCCES; NULL on FATAL ERROR
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

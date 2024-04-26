/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/04/26 15:10:29 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	read_input(void)
{
	t_lexer	lex;
	
	lex.token_list = NULL;
	lex.input = NULL;
	lex.input = readline("./minishell ");
	if (lex.input == NULL)
		return (1);
	lex.i = 0;
	if (lex_input(&lex) == 1)
		return (1);
	ft_putlst_fd(lex.token_list, 1);
	return (0);
}

int	lex_input(t_lexer *lex)
{
	t_list	*new_token;

	while (lex->input[lex->i] != '\0')
	{
		while (ft_isspace(lex->input[lex->i]) == true)
			lex->i++;
		if (lex->input[lex->i] == '|')
		{
			new_token = ft_lstnew(PIPE, "|");
			new_token->type = get_pipe_type(lex);
		}
		if (lex->input[lex->i] == '<' || lex->input[lex->i] == '>')
			new_token = get_redir_token(lex);
		else
			new_token = get_word_token(lex);
		if (new_token == NULL)
		{
			if (lex->token_list != NULL)
				ft_lstclear(&lex->token_list);
			return (1);
		}
		ft_lstadd_back(&lex->token_list, new_token);
	}
	return (0);
}

t_list	*get_word_token(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	int		j;

	attr = NULL;
	j = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (ft_isspace(lex->input[lex->i]) == true)
			break ;
		lex->i++;
		j++;
	}
	attr = (char *)malloc((j + 1) * sizeof(char));
	if (attr == NULL)
		return (NULL);
	ft_strlcpy(attr, lex->input + (lex->i - j), j + 1);
	new_token = ft_lstnew(WORD, attr);
	return (new_token);
}

t_type	get_pipe_type(t_lexer *lex)
{
	t_type type;

	if (lex->input[lex->i] == '|')
	{
		type = PIPE;
		lex->i++;
	}
	return (type);
}

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

t_list	*get_redir_token(t_lexer *lex)
{
	t_list	*new_token;
	t_type	type;
	char	*attr;
	int		j;

	attr = NULL;
	type = get_redir_type(lex);
	while (ft_isspace(lex->input[lex->i]) == true)
		lex->i++;
	if (lex->input[lex->i] == '\0')
		return (NULL);
	j = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (ft_isspace(lex->input[lex->i]) == true)
			break ;
		lex->i++;
		j++;
	}
	attr = (char *)malloc((j + 1) * sizeof(char));
	if (attr == NULL)
		return (NULL);
	ft_strlcpy(attr, lex->input + (lex->i - j), j + 1);
	new_token = ft_lstnew(type, attr);
	return (new_token);
}

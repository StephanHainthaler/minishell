/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/23 16:42:55 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <signal.h>

int	read_input(t_minishell *ms)
{
	int	error_check;

	if (initialize_lexer(ms) == 1)
		return (1);
	while (true)
	{
		global_state = 0;
		if (signal(SIGINT, &handle_sigint))
			ms->last_exit_code = 130;
		//signal(SIGQUIT, &handle_signal);
		signal(SIGTERM, SIG_IGN);
		if (global_state == 0 || global_state == 1 || global_state == 2)
			signal(SIGQUIT, SIG_IGN);
		ms->lex->input = readline("./minishell$ ");
		if (ms->lex->input == NULL)
			return (ft_putendl_fd("exit", 2), 1);
		global_state = 3;
		if (ft_are_str_indentical("./minishell", ms->lex->input))
			global_state = 4;
		if (global_state == 3)
			signal(SIGQUIT, &handle_sigquit);
		if (ft_isspace_str(ms->lex->input) == false)
			break ;
	}
	add_history(ms->lex->input);
	error_check = tokenize_input(ms->lex);
	if (error_check == 1)
		return (1);
	if (error_check == 2)
		return (free_lexer(ms->lex), 2);
	if (check_for_expansion(&ms->lex->token_list, ms->envp, ms->last_exit_code) == 1)
		return (1);
	if (check_for_dequotation(&ms->lex->token_list) == 1)
		return (1);
	return (0);
}

int	tokenize_input(t_lexer *lex)
{
	t_list	*new_token;
	int		parse_error;

	parse_error = 0;
	while (lex->input[lex->i] != '\0')
	{
		while (ft_isspace(lex->input[lex->i]) == true)
			lex->i++;
		if (lex->input[lex->i] == '\0')
			break ;
		if (is_token(lex->input[lex->i]) == true)
			new_token = get_non_word_token(lex);
		else
			new_token = get_word_token(lex, &parse_error);
		if (new_token == NULL)
		{
			if (lex->token_list != NULL)
				ft_lstclear(&lex->token_list);
			if (parse_error == 1)
				return (ft_putendl_fd("Expecting quotation closure", 2), 2);
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

t_list	*get_word_token(t_lexer *lex, int *error)
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

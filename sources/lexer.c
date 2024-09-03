/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/16 15:26:59 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Reads the input and converts it into a linked list.
//It will also check and perform possible expansions.
//<PARAM> The main struct of the program.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	get_input(t_minishell *ms)
{
	int	error_check;

	if (initialize_lexer(ms) == 1)
		return (1);
	error_check = read_input(ms->lex);
	if (error_check == 1)
		return (1);
	if (g_code == 2)
		ms->last_exit_code = 130;
	if (g_code == 3)
		ms->last_exit_code = 131;
	if (error_check == 3)
		return (free_lexer(ms->lex), 3);
	error_check = tokenize_input(ms->lex);
	if (error_check == 1)
		return (1);
	if (error_check == 2)
		return (ms->last_exit_code = 1, free_lexer(ms->lex), 2);
	if (check_for_expansion(&ms->lex->token_list, \
		ms->envp, ms->last_exit_code) == 1)
		return (1);
	return (g_code = 0, 0);
}

//Reads the input and stores it in a string in the lexer struct.
//<PARAM> The lexer struct.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 3 on EXIT
int	read_input(t_lexer *lex)
{
	errno = 0;
	while (true)
	{
		signals_interactive();
		lex->input = readline("./minishell$ ");
		if (lex->input == NULL && errno != 0)
			return (1);
		if (lex->input == NULL && errno == 0)
			return (3);
		if (ft_is_same (lex->input, "./minishell ")
			|| (ft_is_same (lex->input, "./minishell")))
			signals(1);
		if (ft_isspace_str(lex->input) == false)
			break ;
		free(lex->input);
	}
	add_history(lex->input);
	return (0);
}

//Takes the input string and splits into specified tokens.
//The tokens will be stored in a linked list in the lexer struct.
//<PARAM> The lexer struct.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/31 14:39:38 by shaintha         ###   ########.fr       */
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
	if (read_input(ms->lex) == 1)
		return (1);
	error_check = tokenize_input(ms->lex);
	if (error_check == 1)
		return (1);
	if (error_check == 2)
		return (ms->last_exit_code = 1, free_lexer(ms->lex), 2);
	if (check_for_expansion(&ms->lex->token_list, ms->envp, ms->last_exit_code) == 1)
		return (1);
	return (0);
}

//Reads the input and stores it in a string in the lexer struct.
//<PARAM> The lexer struct.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	read_input(t_lexer *lex)
{
	while (true)
	{
		signal(SIGINT, &sigint_interactive);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (isatty(fileno(stdin)))
			lex->input = readline("./minishell$ ");
		else
		{
			// char *line;
			lex->input = get_next_line(fileno(stdin));
			// ms->lex->input = ft_strtrim(line, "\n");
			// free(line);
		}
		if (lex->input == NULL)
			return (1);
		//global_code = 2;
		//signal(SIGINT, &sigint_process);
		if (ft_are_str_indentical("./minishell", lex->input))
			global_code = 3;
		signal(SIGINT, &sigint_subshell);
		signal(SIGQUIT, &handle_sigquit);
		if (ft_are_str_indentical("cat", lex->input))
			global_code = 2;
		signal(SIGINT, &sigint_process);
		if (ft_isspace_str(lex->input) == false)
			break ;
	}
	add_history(lex->input);
	// if (ms->lex->input[ft_strlen(ms->lex->input) - 1] == '\\')
	// 	return (ft_putendl_fd("Input cannot end on '\\'", 2), free_lexer(ms->lex), 2);
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

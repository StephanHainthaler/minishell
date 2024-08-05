/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/05 10:36:19 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_code;

//The main loop of the program. A FATAL ERROR (1) and
//a certain SIGNAL (3) will end the loop, while 
// a standard ERROR (2) will start the loop at the top again.
//<PARAM> The main struct of the program & the indicator for checking errors.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	main_loop(t_minishell *ms, int error_check)
{
	while (true)
	{
		error_check = get_input(ms);
		if (error_check == 1)
			return (free_lexer(ms->lex), rl_clear_history(), 1);
		if (error_check == 2)
			continue ;
		if (error_check == 3)
			break ;
		error_check = parse_input(ms);
		if (error_check == 1)
			return (free_lexer(ms->lex), rl_clear_history(), 1);
		if (error_check == 2)
			continue ;
		free_lexer(ms->lex);
		error_check = execute_input(ms);
		if (error_check == 1)
			return (free_executor(ms->exec), 1);
		if (error_check == 2)
			continue ;
		free_executor(ms->exec);
	}
	return (0);
}

//Start of the program. Initiates the main loop of the program.
//<PARAM> The number of main args, the main args & environment pointers.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;
	int			error_check;

	if (argc != 1)
		return (1);
	if (initialize_minishell(&ms, argc, argv, env) == 1)
		return (1);
	error_check = 0;
	if (main_loop(&ms, error_check) == 1)
		return (ft_free_strarr(ms.envp), 1);
	ft_free_strarr(ms.envp);
	ft_putendl_fd("exit", 1);
	return (ms.last_exit_code);
}

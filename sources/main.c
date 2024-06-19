/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/19 08:25:26 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main_loop(t_minishell *ms, int error_check)
{
	while (true)
	{
		error_check = read_input(ms);
		if (error_check == 1)
			return (free_lexer(ms->lex), rl_clear_history(), 1);
		if (error_check == 2)
			continue ;
		error_check = parse_input(ms);
		if (error_check == 1)
			return (free_lexer(ms->lex), rl_clear_history(), 1);
		if (error_check == 2)
			continue ;
		free_lexer(ms->lex);
		if (execute_input(ms) == 1)
			return (free_executor(ms->exec), 1);
		free_executor(ms->exec);
	}
	return (0);
}

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
	return (0);
}

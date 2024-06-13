/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/13 19:23:56 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;
	
	if (argc != 1)
		return (1);
	if (initialize_minishell(&ms, argc, argv, env) == 1)
		return (1);
	while (true)
	{
		if (read_input(&ms) == 1)
			return (free_lexer(ms.lex), ft_free_strarr(ms.envp), rl_clear_history(), 1);
		if (parse_input(&ms) == 1)
			return (free_lexer(ms.lex), free_executor(ms.exec), ft_free_strarr(ms.envp), rl_clear_history(), 1);
		free_lexer(ms.lex);
		// if (handle_builtin(ms.exec->cmds->simp_cmd, ms.exec->envp) == 0)
		// 	return (free_executor(ms.exec), ft_free_strarr(ms.envp), rl_clear_history(), 1);
		if (execute_input(&ms) == 1)
			return (free_executor(ms.exec), free(ms.envp), 1);
		free_executor(ms.exec);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/13 12:22:36 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;
	int			error_check;
	
	if (argc != 1)
		return (1);
	if (initialize_minishell(&ms, argc, argv, env) == 1)
		return (1);
	while (true)
	{
		error_check = read_input(&ms);
		if (error_check == 1)
			return (free_lexer(ms.lex), ft_free_strarr(ms.envp), rl_clear_history(), 1);
		if (error_check == 2)
		{
			free_lexer(ms.lex);
			continue ;
		}
		if (parse_input(&ms) == 1)
			return (free_lexer(ms.lex), free_executor(ms.exec), ft_free_strarr(ms.envp), rl_clear_history(), 1);
		//same check as above but we have no lines :c
		free_lexer(ms.lex);
		if (execute_input(&ms) == 1)
			return (free_executor(ms.exec), free(ms.envp), 1);
		free_executor(ms.exec);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/16 16:59:03 by juitz            ###   ########.fr       */
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
		sigemptyset(&ms.block_mask);
		ms.sa_signal.sa_mask = ms.block_mask;
		sigaddset(&ms.block_mask, SIGTERM);
		sigaddset(&ms.block_mask, SIGQUIT);
		ms.sa_signal.sa_handler = 0;
		ms.sa_signal.sa_flags = SA_SIGINFO;
		ms.sa_signal.sa_sigaction = &ft_handle_signal;
		if (read_input(&ms) == 1)
			free_and_exit(&ms);
		if (parse_tokens_to_struct(&ms) == NULL)
			free_and_exit(&ms);
		/* if (split_command(&ms) == NULL)
			free_and_exit(&ms); */
		free_lexer(ms.lex);
	}
	return (0);
}

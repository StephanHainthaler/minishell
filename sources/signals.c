/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:49:44 by juitz             #+#    #+#             */
/*   Updated: 2024/07/24 15:02:05 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	handle_sigint(int sig_num)
{
	if (sig_num == SIGINT && global_state == 0)
	{
		//printf("\n");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
	else if (sig_num == SIGINT && global_state == 1)
	{
		global_state = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
	else if (sig_num == SIGINT && global_state == 3)
		printf("\n");
	else if (sig_num == SIGINT && global_state == 4)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void handle_sigquit(int sig_num)
{
	if (sig_num == SIGQUIT && global_state == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
}
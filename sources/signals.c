/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:49:44 by juitz             #+#    #+#             */
/*   Updated: 2024/07/19 20:51:30 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <asm-generic/ioctls.h>
#include <unistd.h>

void	handle_signal(int sig_num)
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
	{
		printf("\n");
		rl_redisplay();
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
	}
}
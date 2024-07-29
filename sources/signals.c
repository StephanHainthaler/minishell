/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:49:44 by juitz             #+#    #+#             */
/*   Updated: 2024/07/29 15:54:14 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	sigint_interactive(int sig_num)
{
	if (sig_num == SIGINT)
	{
		//printf("\n");
		global_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
}

void	sigint_heredoc(int sig_num)
{
	if (sig_num == SIGINT && global_code == 1)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		global_code = 130;
		//rl_redisplay();
	}
}

void	sigint_process(int sig_num)
{
	if (sig_num == SIGINT && global_code == 2)
	{
		printf("\n");
		global_code = 130;
	}
}

void	sigint_subshell(int	sig_num)
{
	if (sig_num == SIGINT && global_code == 3)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		global_code = 130;
	}
}

void handle_sigquit(int sig_num)
{
	if (sig_num == SIGQUIT && global_code == 2)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		global_code = 131;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:49:44 by juitz             #+#    #+#             */
/*   Updated: 2024/08/05 10:23:08 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	sigint_interactive(int sig_num)
{
	if (sig_num == SIGINT)
	{
		//printf("\n");
		g_code = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
}

void	sigint_heredoc(int sig_num)
{
	if (sig_num == SIGINT && g_code == 1)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_code = 2;
		//rl_redisplay();
	}
}

void	sigint_process(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		g_code = 2;
	}
}

void	sigint_subshell(int	sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_code = 2;
	}
}

void	handle_sigquit(int sig_num)
{
	if (sig_num == SIGQUIT && g_code == 2)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		g_code = 131;
	}
}
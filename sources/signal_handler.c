/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:49:44 by juitz             #+#    #+#             */
/*   Updated: 2024/08/16 15:24:02 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Handles the signals interactive operations.
//<PARAM> The signal code.
//<RETURN> void
void	sigint_interactive(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_code = SIGINT;
	}
}

//Handles the signals subshell operations.
//<PARAM> The signal code.
//<RETURN> void
void	sigint_subshell(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_code = SIGINT;
	}
}

//Handles the signals here_doc operations.
//<PARAM> The signal code.
//<RETURN> void
void	sigint_heredoc(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_code = SIGINT;
	}
}

//Handles the signals quitting operations.
//<PARAM> The signal code.
//<RETURN> void
void	handle_sigquit(int sig_num)
{
	if (sig_num == SIGQUIT)
		g_code = SIGQUIT;
}

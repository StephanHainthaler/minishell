/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:59:49 by juitz             #+#    #+#             */
/*   Updated: 2024/08/16 15:21:53 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Sets the current signal mode to the mode given.
//<PARAM> The intended mode.
//<RETURN> void
void	signals(int mode)
{
	if (mode == 0)
		signals_interactive();
	if (mode == 1)
		signals_subshell();
	if (mode == 3)
		signals_heredoc();
}

//Sets the current signal mode to interactive mode.
//<PARAM> void
//<RETURN> void
void	signals_interactive(void)
{
	signal(SIGINT, &sigint_interactive);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

//Sets the current signal mode to subshell mode.
//<PARAM> void
//<RETURN> void
void	signals_subshell(void)
{
	signal(SIGINT, &sigint_subshell);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

//Sets the current signal mode to here_doc mode.
//<PARAM> void
//<RETURN> void
void	signals_heredoc(void)
{
	signal(SIGINT, &sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

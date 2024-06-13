/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:41:38 by juitz             #+#    #+#             */
/*   Updated: 2024/06/13 14:05:20 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGINT)
		return ;
}

int	signals()
{
	sigemptyset(&ms->block_mask);
	ms->sa_signal.sa_mask = ms->block_mask;
	sigaddset(&ms->block_mask, SIGTERM);
	sigaddset(&ms->block_mask, SIGQUIT);
	ms->sa_signal.sa_handler = 0;
	ms->sa_signal.sa_flags = SA_SIGINFO;
	ms->sa_signal.sa_sigaction = &ft_handle_signal;
	return (0);
}
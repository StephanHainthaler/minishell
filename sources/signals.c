/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:49:44 by juitz             #+#    #+#             */
/*   Updated: 2024/07/07 19:12:43 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/readline.h>

void	handle_signal(int sig_num)
{
	if (sig_num == SIGINT/*  && global_state == 0 */)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// if (sig_num == SIGINT && global_state == 1)
	// 	return ;
}
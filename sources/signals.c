/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:24:41 by julian            #+#    #+#             */
/*   Updated: 2024/08/02 10:27:04 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void signals_interactive(void)
{
	signal(SIGINT, &sigint_interactive);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
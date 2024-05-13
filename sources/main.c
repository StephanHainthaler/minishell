/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/13 17:46:48 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;
	
	if (argc != 1)
		return (1);
	ms.argc = argc;
	ms.argv = argv;
	ms.envp = env;
	while (true)
	{
		if (read_input(&ms) == 1)
			return (1);
	}
	return (0);
}

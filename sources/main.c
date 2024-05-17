/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/17 15:14:20 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;
	int flag = 0;
	
	if (argc != 1)
		return (1);
	if (initialize_minishell(&ms, argc, argv, env) == 1)
		return (1);
	while (true)
	{
		//signals(&ms);
		if (read_input(&ms) == 1)
			free_and_exit(&ms);
		if (flag == 0)
		{
			printf("%s\n", ms.lex->input);
			flag = 1;
		}
		if (split_commands(&ms) == NULL)
			free_and_exit(&ms);
		/* if (split_command(&ms) == NULL)
			free_and_exit(&ms); */
		free_lexer(ms.lex);
	}
	return (0);
}

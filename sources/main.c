/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:32 by shaintha          #+#    #+#             */
/*   Updated: 2024/04/22 15:34:07 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_input(void)
{
	char	*input;
	
	input = readline("./minishell ");
	if (input == NULL)
		return (1);
	printf("%s\n", input);
	return (0);
}

int	main(int argc, char *argv[])
{
	printf("Start of minishell-test!: %d %s\n", argc, argv[0]);
	while (true)
	{
		if (handle_input() == 1)
			break ;
	}
	return (0);
}

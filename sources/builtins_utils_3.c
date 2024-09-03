/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:24:15 by juitz             #+#    #+#             */
/*   Updated: 2024/08/12 10:29:29 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Handles and counts the amount of n_flags for teh ft_echo() function.
//<PARAM> The current simple command & the pointer to the n_flag.
//<RETURN> The number of n_flag on SUCCESS
size_t	parse_flag_n(char **simp_cmd, size_t *flag_n)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	*flag_n = 0;
	while (simp_cmd[i])
	{
		if (ft_strncmp(simp_cmd[i], "-n", 2) == 0)
		{
			j = 2;
			while (simp_cmd[i][j] == 'n')
				j++;
			if (simp_cmd[i][j] == '\0')
			{
				*flag_n = 1;
				i++;
				continue ;
			}
		}
		break ;
	}
	return (i);
}

//Prints the string like echo to the output. 
//<PARAM> The current simple command, the starting index & 
//<PARAM> the number of n_flags.
//<RETURN> void
void	print_echo(char **simp_cmd, size_t start_index, size_t flag_n)
{
	size_t	i;

	i = start_index;
	while (simp_cmd[i])
	{
		ft_putstr_fd(simp_cmd[i], 1);
		if (simp_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}

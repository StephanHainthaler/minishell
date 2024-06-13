/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/06/13 09:39:12 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	sort_strarray(char **strarray)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (strarray[i])
	{
		j = i + 1;
		while (strarray[j])
		{
			if (ft_strncmp(strarray[i], strarray[j], ft_strlen(strarray[i])) > 0)
			{
				temp = strarray[i];
				strarray[i] = strarray[j];
				strarray[j] = temp;
			}
			j++;
		}
		i++;
	}
	ft_putstrarr_fd(strarray, 1);
}
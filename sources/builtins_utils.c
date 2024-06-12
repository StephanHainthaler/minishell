/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/06/12 14:34:17 by juitz            ###   ########.fr       */
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
}
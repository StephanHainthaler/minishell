/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:01 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/14 12:57:42 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

bool	ft_isspace_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	ft_isspace(int c)
{
	if (c == ' ' || c == '\f'
		|| c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (true);
	else
		return (false);
}

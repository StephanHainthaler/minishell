/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/06/24 13:35:14 by shaintha         ###   ########.fr       */
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

bool	ft_are_str_indentical(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (false);
	if (ft_strncmp(str1, str2, ft_strlen(str1)) != 0)
		return (false);
	return (true);
}


bool	is_replacable(char *str1, char *str2)
{
	int	i;

	i = 0;
	// while (str1[i] && str1[i] != '=')
	// 	i++;
	// if (ft_strlen(str1) != ft_strlen(str2))
	// 	return (false);
	if (ft_strncmp(str1, str2, i) != 0)
		return (false);
	// if (str2[i] != '\0' || str2[i] != '=')
	// 	return (false);
	return (true);
}

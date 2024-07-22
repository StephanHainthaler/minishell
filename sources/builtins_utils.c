/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/07/22 10:22:48 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	sort_strarray(char **strarray)
{
	char	**arrdup;
	char	*temp;
	int		i;
	int		j;

	arrdup = ft_strarrdup(strarray);
	if (arrdup == NULL)
		return (1);
	i = 0;
	while (arrdup[i])
	{
		j = i + 1;
		while (arrdup[j])
		{
			if (ft_strncmp(arrdup[i], arrdup[j], ft_strlen(arrdup[i])) > 0)
			{
				temp = arrdup[i];
				arrdup[i] = arrdup[j];
				arrdup[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (ft_putstrarr_fd(arrdup, 1), ft_free_strarr(arrdup), 0);
}

// void	print_strarr_sorted(char **strarr)
// {
// 	char	*temp;
// 	size_t	i;
// 	int		j;

// 	if (strarr == NULL)
// 		return ;
	
// 	i = 0;
// 	while (i < ft_strarrlen(strarr))
// 	{
// 		j = 0;
// 		while (strarr[j])
// 		{
// 			if (i == 0)
// 				temp = strarr[0];
// 			if (ft_strncmp(temp, strarr[j], ft_strlen(strarr[j])) > 0 && ft_strncmp(temp, strarr[j], ft_strlen(strarr[j])) != 0)
// 				temp = strarr[j];
// 			j++;
// 		}
// 		ft_putendl_fd(temp, 1);
// 		i++;
// 	}
// }

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

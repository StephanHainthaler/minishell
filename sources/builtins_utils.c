/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/07/22 13:12:25 by shaintha         ###   ########.fr       */
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
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (str2[i] != '\0' && str2[i] != '=')
		i++;
	return (check_for_env(str1, str2, i));
}

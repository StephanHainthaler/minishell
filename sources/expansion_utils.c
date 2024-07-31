/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/31 11:51:16 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_envname_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i] != '\0' && ft_isspace(str[*i]) == false
		&& str[*i] != '\'' && str[*i] != '"') // && str[*i] != '\\')
	{
		if (str[*i + 1] == '$')
		{
			len++;
			break ;
		}
		*i = *i + 1;
		len++;
	}
	return (len);
}

bool	check_for_env(char *str1, char *str2, int len)
{
	if (ft_strncmp(str1, str2, len) != 0)
		return (false);
	if (str1[len] == '=' || str1[len] == '\0')
		return (true);
	return (false);
}

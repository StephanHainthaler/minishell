/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/20 10:39:31 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_envname_len(t_list *node, int *i)
{
	int	len;

	len = 0;
	while (node->attr[*i] != '\0' && ft_isspace(node->attr[*i]) == false
		&& node->attr[*i] != '\'' && node->attr[*i] != '"')
	{
		if (node->attr[*i + 1] == '$')
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
	if (str1[len] == '=')
		return (true);
	return (false);
}

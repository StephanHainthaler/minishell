/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/05 10:00:37 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Checks for special cases for expansion for the current node.
//<PARAM> The current node, the last exit code & the position in the string.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND
int	handle_special_expansion(t_list *node, int exit_code, int *i)
{
	if (node->attr == NULL)
		return (0);
	if (node->attr[*i + 1] == '?')
		return (node->attr = handle_exit_code_expansion(\
			node->attr, exit_code, i), 0);
	if (ft_isspace(node->attr[*i + 1]) == true || node->attr[*i + 1] == '\0'
		|| node->attr[*i + 1] == '$'
		|| (node->attr[*i + 1] == '\'' && ((node->attr[*i + 2] == '\0') \
		|| ft_isspace((node->attr[*i + 2]) == true)))
		|| (node->attr[*i + 1] == '"' && ((node->attr[*i + 2] == '\0') \
		|| ft_isspace((node->attr[*i + 2]) == true))))
		return (0);
	return (1);
}

//Measures the length thats need for the expansion.
//<PARAM> The string to be measured & the position in the string.
//<RETURN> The measured length on SUCCESS
int	get_envname_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i] != '\0' && ft_isspace(str[*i]) == false
		&& str[*i] != '\'' && str[*i] != '"')
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

//Checks, if the environment variable is the same as the second string.
//<PARAM> The environment variable, the second string &
//<PARAM> the length to be compared.
//<RETURN> bool
bool	check_for_env(char *str1, char *str2, int len)
{
	if (ft_strncmp(str1, str2, len) != 0)
		return (false);
	if (str1[len] == '=' || str1[len] == '\0')
		return (true);
	return (false);
}

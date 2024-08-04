/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/07/31 10:04:46 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Allocates, sorts and prints an array of strings.
//After printing, the allocated memory will be freed.
//<PARAM> The array to be sorted.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
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

//Compares two strings in its characters and its length.
//<PARAM> The two strings to be compared.
//<RETURN> bool
bool	ft_are_str_indentical(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (false);
	if (ft_strncmp(str1, str2, ft_strlen(str1)) != 0)
		return (false);
	return (true);
}

//Checks for replacablility for ft_export().
//<PARAM> The two strings to be compared.
//<RETURN> bool
bool	is_replacable(char *str1, char *str2)
{
	int	i;

	if (str1 == NULL)
		return (false);
	i = 0;
	while (str2[i] != '\0' && str2[i] != '=')
		i++;
	return (check_for_env(str1, str2, i));
}

//Figures out the exit code for the ft_exit() function.
//<PARAM> The current simple command & the last exit code.
//<RETURN> The exit code on SUCCESS; -1 on standard ERROR
int	get_exitcode(char **simp_cmd, int last_exit_code)
{
	char 	*exitcode_str;
	int		exitcode;

	if (ft_strarrlen(simp_cmd) == 1)
		return (last_exit_code = global_code, last_exit_code);
	if (ft_strarrlen(simp_cmd) > 2)
		return (ft_putendl_fd("exit\nexec: exit: too many arguments", 2), -1);
	exitcode_str = simp_cmd[1];
	if (ft_isnumber(exitcode_str) == false || ft_isint(exitcode_str) == false)
	{
		ft_putstr_fd("exit\nexec: exit: ", 2);
		ft_putstr_fd(exitcode_str, 2);
		return (ft_putendl_fd(": numeric argument required", 2), 2);
	}
	exitcode = ft_atoi(exitcode_str);
	while (exitcode < 0)
		exitcode = exitcode + 256;
	while (exitcode > 255)
		exitcode = exitcode - 256;
	return (exitcode);
}

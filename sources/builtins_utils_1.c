/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/08/13 10:41:44 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Figures out the exit code for the ft_exit() function.
//<PARAM> The current simple command & the last exit code.
//<RETURN> The exit code on SUCCESS; -1 on standard ERROR
int	get_exitcode(char **simp_cmd, int last_exit_code)
{
	char	*exitcode_str;
	int		exitcode;

	if (ft_strarrlen(simp_cmd) == 1)
		return (last_exit_code);
	exitcode_str = simp_cmd[1];
	if (ft_isnumber(exitcode_str) == false || ft_isint(exitcode_str) == false)
	{
		ft_putstr_fd("exec: exit: ", 2);
		ft_putstr_fd(exitcode_str, 2);
		return (ft_putendl_fd(": numeric argument required", 2), 2);
	}
	if (ft_strarrlen(simp_cmd) > 2)
		return (ft_putendl_fd("exec: exit: too many arguments", 2), -1);
	exitcode = ft_atoi(exitcode_str);
	if (exitcode < 0)
		exitcode = 256 - ((exitcode * -1) % 256);
	if (exitcode > 255)
		exitcode = exitcode % 256;
	return (exitcode);
}

//Sorts and prints the "declares -x" of the environment pointers.
//After printing, the allocated memory will be freed.
//<PARAM> The environment pointers to be sorted.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	print_declare(char **envp)
{
	char	**arrdup;
	size_t	i;
	size_t	j;

	arrdup = ft_sort_strarr(envp);
	if (arrdup == NULL)
		return (1);
	i = 0;
	while (i < ft_strarrlen(arrdup))
	{
		printf("declare -x ");
		j = 0;
		while (arrdup[i][j] != '\0' && arrdup[i][j] != '=')
			printf("%c", arrdup[i][j++]);
		if (arrdup[i][j] == '=')
		{
			printf("=\"");
			printf("%s", arrdup[i] + j + 1);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	return (ft_free_strarr(arrdup), 0);
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

//Checks if exportation is possible with the given string.
//<PARAM> The string to be exported, the exector struct &
//<PARAM> the current number of string to be exported.
//<RETURN> bool
bool	is_exportable(char *to_export, t_executor *exec, size_t *i)
{
	if (to_export[0] == '-' && ft_strchr(to_export, '='))
	{
		ft_putendl_fd("export: usage: export [name[=value] ...]", 2);
		*i = *i + 1;
		exec->exit_status = 2;
		return (false);
	}
	if (to_export == NULL || to_export[0] == '='
		|| is_valid_identifier(to_export) == false)
	{
		ft_putstr_fd("-exec: export `", 2);
		ft_putstr_fd(to_export, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		exec->exit_status = 1;
		*i = *i + 1;
		return (false);
	}
	return (true);
}

//Checks the indicator for compatibility for the ft_export function.
//<PARAM> The string containing the indicator.
//<RETURN> bool
bool	is_valid_identifier(char *to_export)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (true)
	{
		if (to_export[j] == '\0' || to_export[j] == '=')
			break ;
		j++;
	}
	i = 0;
	while (i < j)
	{
		if (i == 0)
			if (ft_isdigit(to_export[i]) == true)
				return (false);
		if (ft_isalnum(to_export[i]) == false && to_export[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

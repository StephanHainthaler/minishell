/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/06/11 15:43:16 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_builtin(char **simp_cmd, char **envp)
{
	if (ft_strncmp(simp_cmd[0], "echo", ft_strlen(simp_cmd[0])) == 0)
		return (scuffed_echo(simp_cmd), 0);
	if (ft_strncmp(simp_cmd[0], "cd", ft_strlen(simp_cmd[0])) == 0)
		return (cd(), 0);
	// if (ft_strncmp(simp_cmd[0], "pwd", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (pwd(), 0);
	// if (ft_strncmp(simp_cmd[0], "export", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (export(), 0);
	// if (ft_strncmp(simp_cmd[0], "unset", ft_strlen(simp_cmd[0])) == 0)
	//	return (0); //return (unset(), 0);
	if (ft_strncmp(simp_cmd[0], "env", ft_strlen(simp_cmd[0])) == 0)
		return (ft_putstrarr_fd(envp, 1), 0);
	if (ft_strncmp(simp_cmd[0], "exit", ft_strlen(simp_cmd[0])) == 0)
		return (0);
	else
		return (1);
}

void scuffed_echo(char **simp_cmd)
{
	int	i;

	i = 1;
	while (simp_cmd[i])
	{
		ft_putstr_fd(simp_cmd[i], 1);
		if (simp_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void scuffed_cd(char **simp_cmd)
{
	if (ft_strarrlen(simp_cmd) == 1)
	{
		if (chdir(getenv("HOME")) == -1)
			ft_error("cd: HOME not set\n");
	}
	else if (ft_strarrlen(simp_cmd) == 2)
	{
		if (chdir(simp_cmd[1]) == -1)
			ft_error("cd: no such file or directory\n");
	}
	else
		ft_putstr_fd("cd: too many arguments\n", 2);
}

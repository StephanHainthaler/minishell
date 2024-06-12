/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/06/12 16:38:24 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <string.h>

int	handle_builtin(char **simp_cmd, t_executor exec)
{
	if (ft_strncmp(simp_cmd[0], "echo", ft_strlen(simp_cmd[0])) == 0)
		return (scuffed_echo(simp_cmd), 0);
	if (ft_strncmp(simp_cmd[0], "cd", ft_strlen(simp_cmd[0])) == 0)
		return (scuffed_cd(simp_cmd), 0);
	if (ft_strncmp(simp_cmd[0], "pwd", ft_strlen(simp_cmd[0])) == 0)
		return (scuffed_pwd(simp_cmd), 0);
	if (ft_strncmp(simp_cmd[0], "export", ft_strlen(simp_cmd[0])) == 0)
		return (scuffed_export(simp_cmd, exec.envp), 0);
	if (ft_strncmp(simp_cmd[0], "unset", ft_strlen(simp_cmd[0])) == 0)
		return (scuffed_unset(simp_cmd, exec.envp), 0);
	if (ft_strncmp(simp_cmd[0], "env", ft_strlen(simp_cmd[0])) == 0)
		return (ft_putstrarr_fd(exec.envp, 1), 0);
	if (ft_strncmp(simp_cmd[0], "exit", ft_strlen(simp_cmd[0])) == 0)
		return (0);
	else
		return (1);
}

void	scuffed_echo(char **simp_cmd)
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
	if ((ft_strarrlen(simp_cmd) == 1) || ft_strncmp(simp_cmd[1], "-n", ft_strlen(simp_cmd[0])) != 0)
		ft_putstr_fd("\n", 1);
}

void	scuffed_cd(char **simp_cmd)
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
		ft_putendl_fd("cd: too many arguments", 2);
}

void	scuffed_pwd(char **simp_cmd)
{
	if (ft_strarrlen(simp_cmd) == 1)
		ft_putendl_fd(getcwd(NULL, 0), 1);
	else
		ft_putendl_fd("pwd: too many arguments", 2);
}
void	scuffed_export(char **simp_cmd, char **envp)
{
	if (ft_strarrlen(simp_cmd) == 1)
		sort_strarray(simp_cmd);
	else if //variable == set
		//free old_var;
		ft_stradd_tostrarr(exec.envp, simp_cmd[1]);
	else if //variable == unset
		ft_stradd_tostrarr(exec.envp, simp_cmd[1]);
}

void	scuffed_unset(char **simp_cmd, char **envp)
{
	int i;

	i = 0;
	while (envp != NULL)
	{
		if (strncmp(simp_cmd[1], envp[i], ft_strlen(envp[i])) == 0)
			envp[i] = NULL;
		i++;
	}
}
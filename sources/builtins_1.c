/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/06/17 11:00:43 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <string.h>

int	handle_builtin(char **simp_cmd, t_executor *exec)
{
	if (ft_are_str_indentical(simp_cmd[0], "echo") == true)
		return (scuffed_echo(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (scuffed_cd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "pwd") == true)
		return (scuffed_pwd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
		return (scuffed_export(simp_cmd, exec->envp), 0);
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
		return (scuffed_unset(simp_cmd, exec->envp), 0);
	if (ft_are_str_indentical(simp_cmd[0], "env") == true)
		return (ft_putstrarr_fd(exec->envp, 1), 0);
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		return (0);
	else
		return (1);
}

int	handle_builtins_non_pipable(t_minishell *ms)
{
	char **simp_cmd;

	simp_cmd = ms->exec->cmds[0]->simp_cmd;
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (scuffed_cd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		ms->envp = scuffed_export(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			free_and_exit(ms);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		if (scuffed_unset(simp_cmd, ms->envp) == 1)
			free_and_exit(ms);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		free_and_exit(ms);
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
			ft_putendl_fd("cd: HOME not set\n", 2);
	}
	else if (ft_strarrlen(simp_cmd) == 2)
	{
		if (chdir(simp_cmd[1]) == -1)
			ft_putendl_fd("cd: no such file or directory\n", 2);
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

char	**scuffed_export(char **simp_cmd, char **envp)
{
	int	i;

	printf("FUCK\n");
	if (ft_strarrlen(simp_cmd) == 1)
		return (sort_strarray(envp), envp);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(simp_cmd[1], envp[i], ft_strlen(simp_cmd[1])) == 0)
		{
			//replace on envp[i]
			return (envp);
		}
		i++;
	}
	envp = ft_stradd_tostrarr(envp, simp_cmd[1]);
	if (envp == NULL)
		return (NULL);
	return (envp);
}

int	scuffed_unset(char **simp_cmd, char **envp)
{
	int i;

	printf("Suffed unset\n");
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(simp_cmd[1], envp[i], ft_strlen(simp_cmd[1])) == 0)
		{
			printf("Found to delete %s\n", envp[i]);
			free(envp[i]);
			envp[i] = NULL;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/07/04 14:35:25 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <string.h>

int	handle_builtin(char **simp_cmd, t_executor *exec)
{
	if (ft_are_str_indentical(simp_cmd[0], "echo") == true)
		return (ft_echo(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (ft_cd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "pwd") == true)
		return (ft_pwd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		exec->envp = ft_export(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (-1);
		return (ft_export(simp_cmd, exec->envp), 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
		return (ft_unset(simp_cmd, exec->envp), 0);
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
		return (ft_cd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		ms->envp = ft_export(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			free_and_exit(ms);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		ms->envp = ft_unset(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			free_and_exit(ms);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		free_and_exit(ms);
	return (1);
}

void	ft_echo(char **simp_cmd)
{
	int	i;

	i = 1;
	while (simp_cmd[i])
	{
		if (ft_strncmp(simp_cmd[1], "-n", ft_strlen(simp_cmd[1])) == 0)
            i++;
		ft_putstr_fd(simp_cmd[i], 1);
		if (simp_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if ((ft_strarrlen(simp_cmd) == 1) || ft_strncmp(simp_cmd[1], "-n", ft_strlen(simp_cmd[0])) != 0)
		ft_putstr_fd("\n", 1);
}

void	ft_cd(char **simp_cmd)
{
    char *oldpwd;
	char *pwd;
	
	oldpwd = getcwd(NULL, 0);
	if (ft_strarrlen(simp_cmd) == 1)
    {
        if (chdir(getenv("HOME")) == -1)
            ft_putendl_fd("cd: HOME not set\n", 2);
    }
	else if (ft_strarrlen(simp_cmd) == 2)
    {
        if (chdir(simp_cmd[1]) == -1)
        {
            ft_putendl_fd("cd: no such file or directory\n", 2);
            return (free(oldpwd));
        }
    }
	else
    {
        ft_putendl_fd("cd: too many arguments", 2);
		return (free(oldpwd));
    }
    setenv("OLDPWD", oldpwd, 1);
    free(oldpwd);
    pwd = getcwd(NULL, 0);
    setenv("PWD", pwd, 1);
    free(pwd);
}

/* void	ft_cd(char **simp_cmd)
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
} */

void	ft_pwd(char **simp_cmd)
{
	if (ft_strarrlen(simp_cmd) == 1)
		ft_putendl_fd(getcwd(NULL, 0), 1);
	else
		ft_putendl_fd("pwd: too many arguments", 2);
}

char	**ft_export(char **simp_cmd, char **envp)
{
	int		i;
	int		j;
	bool	found;

	if (ft_strarrlen(simp_cmd) == 1)
		return (sort_strarray(envp), envp);
	i = 1;
	while (i < (int)ft_strarrlen(simp_cmd))
	{
		j = 0;
		while (envp[j] != NULL)
		{
			found = false;
			//printf("simp_cmd%i - Test%i: %s\n", i, j, envp[j]);
			//if (is_replacable(envp[j], simp_cmd[i]) == true)
			if (check_for_env(envp[j], simp_cmd[i], ft_strlen(simp_cmd[i])) == true)
			{
				printf("Found\n");
				envp = ft_strreplace_instrarr(envp, simp_cmd[i], j);
				if (envp[j] == NULL)
					return (NULL);
				j = ft_strarrlen(envp);
				found = true;
				continue ;
			}
			j++;
		}
		if (found == false)
		{
			envp = ft_stradd_tostrarr(envp, simp_cmd[i]);
			if (envp == NULL)
				return (NULL);
		}
		i++;
	}
	return (envp);
}

char	**ft_unset(char **simp_cmd, char **envp)
{
	char	**new_envp;
	bool	is_new;
	int		i;
	int		pos;

	is_new = false;
	i = 1;
	while (i < (int)ft_strarrlen(simp_cmd))
	{
		pos = 0;
		while (envp[pos] != NULL)
		{
			if (check_for_env(envp[pos++], simp_cmd[i], ft_strlen(simp_cmd[i])) == false)
				continue ;
			new_envp = ft_strdel_fromstrarr(envp, pos - 1);
			if (new_envp == NULL)
				return (ft_free_strarr(new_envp), NULL);
			is_new = true;
		}
		i++;
	}
	if (is_new == false)
		return (envp);
	return (new_envp);
}

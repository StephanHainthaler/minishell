/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/07/31 15:58:56 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_echo(char **simp_cmd)
{
	int	i;
	int	j;
	int flag_n;
	
	i = 1;
	j = 0;
	flag_n = 0;

	while (simp_cmd[i])
	{
		if (ft_strncmp(simp_cmd[i], "-n", 2) == 0)
		{
			j = 2;
			j = 2;
			while (simp_cmd[i][j] == 'n')
				j++;
			if (simp_cmd[i][j] == '\0')
			{
				flag_n = 1;
				i++;
				continue;
			}
		}
		break;
	}
	while (simp_cmd[i])
	{
		ft_putstr_fd(simp_cmd[i], 1);
		if (simp_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}

void	ft_cd(char **simp_cmd, char **envp)
{
    char *oldpwd;
	char *pwd;
	int		i;
	
	oldpwd = getcwd(NULL, 0);
	//ERROR_CHECK
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
	i = 0;
	while (envp[i] != NULL) 
	{	
		if (ft_strncmp("OLDPWD=", envp[i], 7) == false)
			break ;
		i++;
	}
	oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	//NULL CHECK
	envp = ft_strreplace_instrarr(envp, oldpwd, i);
	//NULL CHECK
    free(oldpwd);
	
    pwd = getcwd(NULL, 0);
	//ERROR CHECK
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", envp[i], 4) == false)
			break ;
		i++;
	}
	pwd = ft_strjoin("PWD=", pwd);
	//NULL CHECK
	envp = ft_strreplace_instrarr(envp, pwd, i);
	//NULL CHECK
    free(pwd);
}

void	ft_pwd(char **simp_cmd)
{
	if (ft_strarrlen(simp_cmd) == 1)
		ft_putendl_fd(getcwd(NULL, 0), 1);
	//ERROR_CHECK
	else
		ft_putendl_fd("pwd: too many arguments", 2);
}

char	**ft_export(char **simp_cmd, char **envp)
{
	int		i;
	int		pos;
	bool	found;

	if (ft_strarrlen(simp_cmd) == 1)
	{
		if (sort_strarray(envp) == 1)
			return (NULL);
		return (envp);
	}
	i = 1;
	while (i < (int)ft_strarrlen(simp_cmd))
	{
		found = false;
		pos = 0;
		while (envp[pos] != NULL && is_replacable(envp[pos], simp_cmd[i]) == false)
			pos++;
		if (is_replacable(envp[pos], simp_cmd[i]) == true)
		{
			found = true;
			envp = ft_strreplace_instrarr(envp, simp_cmd[i], pos);
			if (envp[pos] == NULL)
				return (NULL);
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
	int		i;
	int		pos;

	if (ft_strarrlen(simp_cmd) == 1)
		return (envp);
	i = 1;
	while (i < (int)ft_strarrlen(simp_cmd))
	{
		pos = 0;
		while (envp[pos] != NULL)
		{
			if (check_for_env(envp[pos], simp_cmd[i], \
				ft_strlen(simp_cmd[i])) == false)
			{
				pos++ ;
				continue ;
			}
			envp = ft_strdel_fromstrarr(envp, pos);
			if (envp == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	return (envp);
}

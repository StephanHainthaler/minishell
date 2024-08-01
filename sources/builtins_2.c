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

int		ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putendl_fd("pwd: fatal error", 1);
		return (1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int		ft_cd(char **simp_cmd, char **envp)
{
	char	*pwd;
    char	*oldpwd;

	pwd = NULL;
	if (ft_strarrlen(simp_cmd) > 2)
		return (ft_putendl_fd("cd: too many arguments", 2), 2);
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (ft_putendl_fd("cd: fatal error", 2), 1);
	if (ft_strarrlen(simp_cmd) == 1)
    {
		if (is_env_set(envp, "HOME=") == false)
			return (free(oldpwd), ft_putendl_fd("cd: HOME not set", 2), 2);
		pwd = get_env(envp, "HOME=");
		if (pwd == NULL)
			return (free(oldpwd), ft_putendl_fd("cd: fatal error", 2), 1);
        if (chdir(pwd) == -1) //fatal or not?  if not change exit to 2
            return (free(pwd), free(oldpwd), ft_putendl_fd("cd: fatal error", 2), 1);
    }
	if (ft_strarrlen(simp_cmd) == 2)
        if (chdir(simp_cmd[1]) == -1) //fatal or not? if not change exit to 2
            return (free(oldpwd), ft_putendl_fd("cd: no such file or directory", 2), 1);
	envp = update_pwds_in_env(envp, pwd, oldpwd);
	if (envp == NULL)
		return (ft_putendl_fd("cd: fatal error", 2), 1);
	return (0);
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

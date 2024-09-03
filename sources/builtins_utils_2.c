/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:04:46 by juitz             #+#    #+#             */
/*   Updated: 2024/08/13 10:26:24 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Changes the current directory to the home directory set in environment.
//If the input does not have the necessary arguments, 
//this function will return with doing anything.
//<PARAM> The current simple command, the environment pointers &
//<PARAM> the executor struct.
//<RETURN> 0 on SUCCESS; 1 on not FOUND;
//<RETURN> 2 on standard ERROR; -1 on FATAL ERROR
int	change_to_home_directory(char **simp_cmd, char **envp, t_executor *exec)
{
	char	*home;

	if (ft_strarrlen(simp_cmd) == 1 || (ft_strarrlen(simp_cmd) == 2
			&& ft_is_same(simp_cmd[1], "--") == true))
	{
		home = NULL;
		if (is_env_set(envp, "HOME=") == false)
			return (ft_putendl_fd("-exec: cd: HOME not set", 2),
				exec->exit_status = 1, 2);
		home = get_env_var(envp, "HOME=");
		if (home == NULL)
			return (exec->exit_status = 1, ft_putendl_fd("cd: FATAL", 2), -1);
		if (chdir(home) == -1)
		{
			ft_putstr_fd("exec: cd: ", 2);
			ft_putstr_fd(simp_cmd[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (exec->exit_status = 1, free(home), 2);
		}
		return (exec->exit_status = 0, free(home), 0);
	}
	return (1);
}

//Changes the current directory to the another directory.
//If the input does not have the necessary arguments, 
//this function will return with doing anything.
//<PARAM> The current simple command, the environment pointers &
//<PARAM> the executor struct.
//<RETURN> 0 on SUCCESS; 1 on not FOUND;
//<RETURN> 2 on standard ERROR; -1 on FATAL ERROR
int	change_to_other_directory(char **simp_cmd, char **envp, t_executor *exec)
{
	if (ft_strarrlen(simp_cmd) == 2 && ft_is_same(simp_cmd[1], "--") == false)
	{
		if (ft_is_same(simp_cmd[1], "-") == true)
		{
			if (is_env_set(envp, "OLDPWD=") == false)
				return (exec->exit_status = 1,
					ft_putendl_fd("-exec: cd: OLDPWD not set", 2), 2);
			ft_free(simp_cmd[1]);
			simp_cmd[1] = get_env_var(envp, "OLDPWD=");
			if (simp_cmd[1] == NULL)
				return (exec->exit_status = 1, -1);
			ft_putendl_fd(simp_cmd[1], 1);
		}
		if (chdir(simp_cmd[1]) == -1)
		{
			ft_putstr_fd("exec: cd: ", 2);
			ft_putstr_fd(simp_cmd[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (exec->exit_status = 1, 2);
		}
	}
	return (1);
}

//After changing directories, it updates the PWD variables in environment.
//At the end it will free the memory of both pwd strings.
//<PARAM> The environment pointers, the current working directory &
//<PARAM> the previous working directory.
//<RETURN> The updated environment on SUCCESS; NULL on FATAL ERROR
char	**update_pwds(char **envp, char *pwd, char *oldpwd)
{
	if (is_env_set(envp, "PWD=") == true)
	{
		envp = update_pwd(envp, pwd);
		if (envp == NULL)
			return (ft_free(pwd), free(oldpwd), NULL);
	}
	if (is_env_set(envp, "OLDPWD=") == true)
	{
		envp = update_oldpwd(envp, oldpwd);
		if (envp == NULL)
			return (ft_free(pwd), free(oldpwd), NULL);
	}
	return (ft_free(pwd), free(oldpwd), envp);
}

//This function updates the current working directory in environment.
//<PARAM> The environment pointers & the current working directory.
//<RETURN> The updated environment on SUCCESS; NULL on FATAL ERROR
char	**update_pwd(char **envp, char *pwd)
{
	char	*pwd_env;
	size_t	i;

	i = get_env_var_pos(envp, "PWD=");
	pwd_env = ft_strjoin("PWD=", pwd);
	if (pwd_env == NULL)
		return (ft_free_strarr(envp), NULL);
	envp = ft_strreplace_instrarr(envp, pwd_env, i);
	if (envp == NULL)
		return (free(pwd_env), NULL);
	return (free(pwd_env), envp);
}

//This function updates the previous working directory in environment.
//<PARAM> The environment pointers & the previous working directory.
//<RETURN> The updated environment on SUCCESS; NULL on FATAL ERROR
char	**update_oldpwd(char **envp, char *oldpwd)
{
	char	*oldpwd_env;
	size_t	i;

	i = get_env_var_pos(envp, "OLDPWD=");
	oldpwd_env = ft_strjoin("OLDPWD=", oldpwd);
	if (oldpwd_env == NULL)
		return (ft_free_strarr(envp), NULL);
	envp = ft_strreplace_instrarr(envp, oldpwd_env, i);
	if (envp == NULL)
		return (free(oldpwd_env), NULL);
	return (free(oldpwd_env), envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:46 by juitz             #+#    #+#             */
/*   Updated: 2024/07/31 10:04:46 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_env(char **envp, char *env_name)
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], env_name, ft_strlen(env_name)) == NULL)
			i++;
		else
		{
			env = ft_strdup(envp[i] + ft_strlen(env_name));
			if (env == NULL)
				return (NULL);
			break ;
		}
	}
	return (env);
}

char	**update_pwds_in_env(char **envp, char *pwd, char *oldpwd)
{
	if (is_env_set(envp, "PWD=") == false && is_env_set(envp, "OLDPWD=") == true)
	{
		printf("delete OLDPWD FROM ENV!!!\n");
		//delete OLDPWD FROM ENV!!!
	}
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

char	**update_pwd(char **envp, char *pwd)
{
	char	*pwd_env;
	int 	i;

	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (ft_free_strarr(envp), NULL);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", envp[i], 4) == false)
			break ;
		i++;
	}
	pwd_env = ft_strjoin("PWD=", pwd);
	if (pwd_env == NULL)
		return (ft_free_strarr(envp), NULL);
	envp = ft_strreplace_instrarr(envp, pwd_env, i);
	if (envp == NULL)
		return (free(pwd_env), NULL);
	return (free(pwd_env), envp);
}

char	**update_oldpwd(char **envp, char *oldpwd)
{
	char	*oldpwd_env;
	int 	i;

	i = 0;
	while (envp[i] != NULL) 
	{	
		if (ft_strncmp("OLDPWD=", envp[i], 7) == false)
			break ;
		i++;
	}
	oldpwd_env = ft_strjoin("OLDPWD=", oldpwd);
	if (oldpwd_env == NULL)
		return (ft_free_strarr(envp), NULL);
	envp = ft_strreplace_instrarr(envp, oldpwd_env, i);
	if (envp == NULL)
		return (free(oldpwd_env), NULL);
	return (free(oldpwd_env), envp);
}

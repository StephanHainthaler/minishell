/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:04:46 by juitz             #+#    #+#             */
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

int		get_env_pos(char **envp, char *env_name)
{
	int	pos;

	if (is_env_set(envp, env_name) == false)
		return (-1);
	pos = 0;
	while (envp[pos] != NULL)
	{
		if (ft_strncmp(env_name, envp[pos], ft_strlen(env_name)) == false)
			break ;
		pos++;
	}
	return (pos);
}

char	**update_pwds(char **envp, char *pwd, char *oldpwd)
{
	// if (is_env_set(envp, "PWD=") == false && is_env_set(envp, "OLDPWD=") == true)
	// {
	// 	printf("delete OLDPWD FROM ENV!!!\n");
	// 	envp = ft_strdel_fromstrarr(envp, get_env_pos(envp, "OLDPWD="));
	// 	if (envp == NULL)
	// 		return (ft_free_strarr(envp), ft_free(pwd), free(oldpwd), NULL);
	// }
	if (is_env_set(envp, "PWD=") == true)
	{
		envp = update_pwd(envp, pwd);
		if (envp == NULL)
			return (ft_free(pwd), free(oldpwd), NULL);
	}
	if (is_env_set(envp, "OLDPWD=") == true || is_env_set(envp, "OLDPWD\0") == true)
	{
		if (is_env_set(envp, "OLDPWD=") == true)
			envp = update_oldpwd(envp, oldpwd, false);
		else
			envp = update_oldpwd(envp, oldpwd, true);
		if (envp == NULL)
			return (ft_free(pwd), free(oldpwd), NULL);
	}
	return (ft_free(pwd), free(oldpwd), envp);
}

char	**update_pwd(char **envp, char *pwd)
{
	char	*pwd_env;
	int 	i;

	// if (pwd == NULL)
	// {
	// 	pwd = getcwd(NULL, 0);
	// 	if (pwd == NULL)
	// 		return (ft_free_strarr(envp), NULL);
	// }
	// ft_putendl_fd(pwd, 1);
	i = get_env_pos(envp, "PWD=");
	// while (envp[i] != NULL)
	// {
	// 	if (ft_strncmp("PWD=", envp[i], 4) == false)
	// 		break ;
	// 	i++;
	// }
	pwd_env = ft_strjoin("PWD=", pwd);
	if (pwd_env == NULL)
		return (ft_free_strarr(envp), NULL);
	envp = ft_strreplace_instrarr(envp, pwd_env, i);
	if (envp == NULL)
		return (free(pwd_env), NULL);
	return (free(pwd_env), envp);
}

char	**update_oldpwd(char **envp, char *oldpwd, bool is_first)
{
	char	*oldpwd_env;
	int 	i;

	// i = 0;
	// while (envp[i] != NULL) 
	// {	
	// 	if (ft_strncmp("OLDPWD=", envp[i], 7) == false)
	// 		break ;
	// 	i++;
	// }
	if (is_first == true)
		i = get_env_pos(envp, "OLDPWD\0");
	else
		i = get_env_pos(envp, "OLDPWD=");
	oldpwd_env = ft_strjoin("OLDPWD=", oldpwd);
	if (oldpwd_env == NULL)
		return (ft_free_strarr(envp), NULL);
	envp = ft_strreplace_instrarr(envp, oldpwd_env, i);
	if (envp == NULL)
		return (free(oldpwd_env), NULL);
	return (free(oldpwd_env), envp);
}

char	**increase_shlvl(char **envp)
{
	char	*new_shlvl;
	char	*temp;
	int		shlvl;
	
	temp = get_env(envp, "SHLVL=");
	if (temp == NULL)
		return (ft_free_strarr(envp), NULL);
	shlvl = ft_atoi(temp) + 1;
	free(temp);
	temp = ft_itoa(shlvl);
	if (temp == NULL)
		return (ft_free_strarr(envp), NULL);
	new_shlvl = ft_strjoin("SHLVL=", temp);
	if (new_shlvl == NULL)
		return (free(temp), ft_free_strarr(envp), NULL);
	free(temp);
	envp = ft_strreplace_instrarr(envp, new_shlvl, get_env_pos(envp, "SHLVL="));
	if (envp == NULL)
		return (free(new_shlvl), NULL);
	return (free(new_shlvl), envp);
}

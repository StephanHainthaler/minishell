/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:53:17 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/12 09:38:13 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Takes the environment and increases its current shell level by 1.
//<PARAM> The environment pointers.
//<RETURN> The environment pointers on SUCCESS; NULL on FATAL ERROR
char	**increase_shlvl(char **envp)
{
	char	*new_shlvl;
	char	*temp;
	int		shlvl;

	temp = get_env_var(envp, "SHLVL=");
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
	envp = ft_strreplace_instrarr(envp, new_shlvl,
			get_env_var_pos(envp, "SHLVL="));
	if (envp == NULL)
		return (free(new_shlvl), NULL);
	return (free(new_shlvl), envp);
}

//Checks if a variable is set in environment. 
//<PARAM> The environment pointers & the name of the variable.
//<RETURN> bool
bool	is_env_set(char *envp[], char *env_name)
{
	size_t	i;

	if (envp == NULL)
		return (false);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], env_name, ft_strlen(env_name)) == NULL)
			i++;
		else
			return (true);
	}
	return (false);
}

//Gets the content of the environment variable.
//The name of the variable needs to have a '=' at the end.
//<PARAM> The environment pointers & the name of the variable.
//<RETURN> The content of the variable on SUCCESS; NULL on FATAL ERROR
char	*get_env_var(char **envp, char *env_name)
{
	char	*env_var;
	size_t	i;

	env_var = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], env_name, ft_strlen(env_name)) == NULL)
			i++;
		else
		{
			env_var = ft_strdup(envp[i] + ft_strlen(env_name));
			if (env_var == NULL)
				return (NULL);
			break ;
		}
	}
	return (env_var);
}

//Gets the position of the environment variable.
//The name of the variable needs to have a '=' at the end.
//<PARAM> The environment pointers & the name of the variable.
//<RETURN> The position of the variable on SUCCESS; -1 on standard ERROR
size_t	get_env_var_pos(char **envp, char *env_name)
{
	size_t	pos;

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

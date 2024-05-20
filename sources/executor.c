/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/14 14:35:56 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**get_paths(t_executor *exec)
{
	char	**paths;
	char	*path_str;
	int		i;

	i = 0;
	while (exec->envp[i] != NULL)
	{
		if (ft_strnstr(exec->envp[i], "PATH=", 5) == NULL)
			i++;
		else
		{
			path_str = ft_strnstr(exec->envp[i], "PATH=", 5);
			ft_strlcpy(path_str, path_str + 5, ft_strlen(path_str) - 4);
			paths = ft_split(path_str, ':');
			if (paths == NULL)
				return (NULL);
			return (paths);
		}
	}
	return (NULL);
}

char	*get_cmd_path(t_executor *exec, int cmd_nbr)
{
	char	*temp;
	int		i;

	// exec->split_cmd = ft_split(exec->cmds[cmd_nbr], ' ');
	// if (exec->split_cmd == NULL)
	// 	return (NULL);

    //get simp_cmd form julian
    //need to simp_cmd[0] for this function instead of split_cmd[0]
	i = 0;
	while (exec->paths[i] != NULL)
	{
		temp = ft_strjoin(exec->paths[i], "/");
		if (temp == NULL)
			return (NULL);
		exec->cmd_path = ft_strjoin(temp, exec->split_cmd[0]);
		if (exec->cmd_path == NULL)
			return (ft_free(temp), free_exec(exec), NULL);
		ft_free(temp);
		if (access(exec->cmd_path, F_OK | X_OK) == 0)
			return (exec->cmd_path);
		ft_free(exec->cmd_path);
		i++;
	}
	return (exec->split_cmd[0]);
}

bool	is_path_set(char *envp[])
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) == NULL)
			i++;
		else
			return (true);
	}
	return (false);
}

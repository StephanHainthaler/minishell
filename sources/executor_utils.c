/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:40:11 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/22 12:53:24 by shaintha         ###   ########.fr       */
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

char	*get_cmd_path(t_executor *exec, t_cmd *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	while (exec->paths[i] != NULL)
	{
		temp = ft_strjoin(exec->paths[i], "/");
		if (temp == NULL)
			return (NULL);
		cmd->cmd_path = ft_strjoin(temp, cmd->simp_cmd[0]);
		if (cmd->cmd_path == NULL)
			return (ft_free(temp), free_executor(exec), NULL);
		ft_free(temp);
		if (access(cmd->cmd_path, F_OK | X_OK) == 0)
			return (cmd->cmd_path);
		ft_free(cmd->cmd_path);
		i++;
	}
	return (cmd->simp_cmd[0]);
}

int	get_fd(char *file, bool is_in_fd)
{
	int	fd;

	if (is_in_fd == true)
		fd = open(file, O_RDONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("exec: ", 2);
		if (ft_strncmp(file, "", 1) == 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			perror(file);
		return (-1);
	}
	return (fd);
}

bool	is_path_set(char *envp[])
{
	int	i;

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

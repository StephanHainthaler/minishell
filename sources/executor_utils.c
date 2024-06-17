/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:40:11 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/17 12:35:50 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**get_paths(t_executor *exec, int *error_flag)
{
	char	**paths;
	char	*path_str;
	int		i;

	i = 0;
	while (exec->envp[i] != NULL)
	{
		if (ft_strncmp(exec->envp[i], "PATH=", 5) != 0)
			i++;
		else
		{
			path_str = ft_strdup(exec->envp[i] + 5);
			if (path_str == NULL)
				return (*error_flag = 1, NULL);
			paths = ft_split(path_str, ':');
			if (paths == NULL)
				return (*error_flag = 1, free(path_str), NULL);
			free(path_str);
			return (*error_flag = 0, paths);
		}
	}
	return (*error_flag = 0, NULL);
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
	return (ft_strdup(cmd->simp_cmd[0]));
}

int	get_fd(char *file, bool is_in_fd, bool is_append)
{
	int	fd;

	if (is_in_fd == true)
		fd = open(file, O_RDONLY, 0777);
	else
	{
		if (is_append == false)
			fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else
			fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
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

int	handle_redirection(t_cmd *cmd)
{
	if (cmd->infile != NULL)
	{
		if (dup2(cmd->in_fd, 0) == -1)
		{
			ft_putendl_fd("infile dup2 failed", 2);
			return (1);
		}
		close(cmd->in_fd);
	}
	if (cmd->outfile != NULL)
	{
		if (dup2(cmd->out_fd, 1) == -1)
		{
			ft_putendl_fd("outfile dup2 failed", 2);
			return (1);
		}
		close(cmd->out_fd);
	}
	return (0);
}

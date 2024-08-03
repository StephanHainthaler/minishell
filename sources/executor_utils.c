/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:40:11 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/29 15:58:46 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Takes PATH from environment and allocates them in an array of strings.
//If PATH has been unset, returning NULL will be considered a standard ERROR.
//<PARAM> The executor struct & a flag for checking a FATAL ERROR.
//<RETURN> The paths on SUCCESS; NULL on FATAL ERROR
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

//Searches the paths for the command name to allocate their path in a string.
//If there was no match, the name of the command will be considered the path.
//<PARAM> The executor struct & the current cmd struct.
//<RETURN> The cmd_path on SUCCESS; NULL on FATAL ERROR
char	*get_cmd_path(t_executor *exec, t_cmd *cmd)
{
	char	*temp;
	int		i;

	if (exec->is_path_set == false)
		return (ft_strdup(cmd->simp_cmd[0]));
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

//Opens and returns the file descriptor of the file given.
//<PARAM> The in/outfile, the type of file & the mode of outfile.
//<RETURN> The fd on SUCCESS; -1 on standard ERROR
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
			ft_putendl_fd(": No such file or directory", 2);
		else
		{
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		return (-1);
	}
	return (fd);
}

//Checks if a variable is set in environment. 
//<PARAM> The environment pointers & the name of the variable.
//<RETURN> bool
bool	is_env_set(char *envp[], char *env_name)
{
	int	i;

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

//Redirects the file descriptors and closes the old ones.
//<PARAM> The current cmd struct, the infile fd & the outfile fd.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	handle_redirection(t_cmd *cmd, int in, int out)
{
	if (cmd->infile != NULL)
	{
		if (dup2(cmd->in_fd, in) == -1)
		{
			ft_putendl_fd("infile dup2 failed", 2);
			return (1);
		}
		close(cmd->in_fd);
	}
	if (cmd->outfile != NULL)
	{
		if (dup2(cmd->out_fd, out) == -1)
		{
			ft_putendl_fd("outfile dup2 failed", 2);
			return (1);
		}
		close(cmd->out_fd);
	}
	return (0);
}

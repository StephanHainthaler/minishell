/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/27 15:33:04 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	execute_input(t_minishell *ms)
{
	if (initialize_executor_2(ms) == 1)
		return (1);
	if (ms->exec->num_of_cmds == 1)
	{
		printf("Start execution\n");
		if (single_execution(ms->exec) == 1)
			return (1);
	}
	// else
	// {
	// 	if (piping(ms->exec) == 1)
	// 		return (1);
	// }
	return (0);
}

int	single_execution(t_executor *exec)
{
	int	status;

	printf("Forking:\n");
	exec->cpids[0] = fork();
	if (exec->cpids[0] == -1)
		return (1);
	if (exec->cpids[0] == 0)
		single_child_proc(exec, exec->cmds[0]);
	printf("Parent: Waiting\n");
	waitpid(exec->cpids[0], &status, 0);
	//free_exec(exec);
	//change last cmd status in ms
	//exit(WEXITSTATUS(status));
	return (0);
}

void	single_child_proc(t_executor *exec, t_cmd *cmd)
{	
	printf("Child: Start\n");
	if (cmd->infile != NULL)
	{
		printf("Child: infile_fd dup\n");
		if (dup2(cmd->in_fd, 0) == -1)
		{
			ft_putendl_fd("dup2 failed", 2);
			//free();
			exit(1);
		}
		close(cmd->in_fd);
	}
	if (cmd->outfile != NULL)
	{
		printf("Child: outfile_fd dup\n");
		if (dup2(cmd->out_fd, 1) == -1)
		{
			ft_putendl_fd("dup2 failed", 2);
			//free();
			exit(1);
		}
		close(cmd->out_fd);
	}
	if (exec->paths != NULL)
	{
		printf("Child: Get the cmd_path\n");
		cmd->cmd_path = get_cmd_path(exec, exec->cmds[0]);
		if (cmd->cmd_path == NULL)
			exit_with_error("malloc error", exec);
		printf("Child: cmd_path = %s\n", cmd->cmd_path);
	}
	printf("Child: Enters execution function\n");
	execute_cmd(exec, exec->cmds[0]);
}

void	execute_cmd(t_executor *exec, t_cmd *cmd)
{
	if (cmd->cmd_path == NULL)
	{
		printf("Child: path env does not exists\n");
		ft_free_strarr(exec->envp);
		free_executor(exec);
		exit(127);
	}
	printf("Child: execute cmd\n");
	if (execve(cmd->cmd_path, cmd->simp_cmd, exec->envp) == -1)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": command not found", 2);
		ft_free_strarr(exec->envp);
		free_executor(exec);
		exit(127);
	}
}

void	exit_with_error(char *error_message, t_executor *exec)
{
	ft_putendl_fd(error_message, 2);
	free_executor(exec);
	exit(EXIT_FAILURE);
}

void	close_free_and_exit(t_executor *exec, int fd1, int fd2)
{
	free_executor(exec);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	exit(EXIT_FAILURE);
}
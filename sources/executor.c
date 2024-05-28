/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/28 11:15:30 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	execute_input(t_minishell *ms)
{
	if (initialize_executor_2(ms) == 1)
		return (1);
	if (ms->exec->num_of_cmds == 1)
	{
		if (single_execution(ms->exec) == 1)
			return (1);
	}
	else
	{
		if (multiple_execution(ms->exec) == 1)
			return (1);
	}
	return (0);
}

int	multiple_execution(t_executor *exec)
{
	int	i;
	int	status;
	int	ends[2];

	i = 0;
	while (i < exec->num_of_pipes)
	{
		if (pipe(ends) == -1)
			return (1);
		exec->cpids[i] = fork();
		if (exec->cpids[i] == -1)
			return (close(ends[0]), close(ends[1]), 1);
		if (exec->cpids[i] == 0)
			child_proc(exec, exec->cmds[i], ends);
		exec->cpids[i + 1] = fork();
		if (exec->cpids[i + 1] == -1)
			return (close(ends[0]), close(ends[1]), 1);
		if (exec->cpids[i + 1] == 0)
			child_proc(exec, exec->cmds[i + 1], ends);
		close(ends[0]);
		close(ends[1]);
		waitpid(exec->cpids[i], NULL, 0);
		waitpid(exec->cpids[i + 1], &status, 0);
		i++;
	}
	return (0);
}

void	child_proc(t_executor *exec, t_cmd *cmd, int ends[])
{
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit_child(exec, ends[0], ends[1], 1);
	if (handle_infile_outfile_dup(cmd) == 1)
		exit_child(exec, ends[0], ends[1], 1);
	if (dup2(ends[1], 1) == -1)
	{
		ft_putendl_fd("dup2 failed", 2);
		exit_child(exec, ends[0], ends[1], 1);
	}
	close(ends[1]);
	if (dup2(ends[0], 0) == -1)
	{
		ft_putendl_fd("dup2 failed", 2);
		exit_child(exec, ends[0], -1, 1);
	}
	close(ends[0]);
	if (exec->paths != NULL)
	{
		cmd->cmd_path = get_cmd_path(exec, exec->cmds[0]);
		if (cmd->cmd_path == NULL)
			exit_child(exec, -1, -1, 1);
	}
	execute_cmd(exec, exec->cmds[0]);
}

int	handle_infile_outfile_dup(t_cmd *cmd)
{
	if (cmd->infile != NULL)
	{
		if (dup2(cmd->in_fd, 0) == -1)
		{
			ft_putendl_fd("dup2 failed", 2);
			return (1);
		}
		close(cmd->in_fd);
	}
	if (cmd->outfile != NULL)
	{
		if (dup2(cmd->out_fd, 1) == -1)
		{
			ft_putendl_fd("dup2 failed", 2);
			return (1);
		}
		close(cmd->out_fd);
	}
	return (0);
}

void	exit_child(t_executor *exec, int end1, int end2, int exit_status)
{
	if (end1 != -1)
		close(end1);
	if (end2 != -1)
		close(end2);
	ft_free_strarr(exec->envp);
	free_executor(exec);
	exit(exit_status);
}
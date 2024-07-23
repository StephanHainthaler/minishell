/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/23 14:19:17 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	single_child_proc(t_executor *exec, t_cmd *cmd)
{	
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit_child(exec, -1, -1, 1);
	if (handle_redirection(cmd) == 1)
		exit_child(exec, -1, -1, 1);
	if (exec->paths != NULL)
	{
		cmd->cmd_path = get_cmd_path(exec, exec->cmds[0]);
		if (cmd->cmd_path == NULL)
		{
			ft_putendl_fd("malloc error", 2);
			exit_child(exec, -1, -1, 1);
		}
	}
	execute_cmd(exec, exec->cmds[0]);
}

void	multi_child_proc(t_executor *exec, t_cmd *cmd, int ends[], int *old_end)
{
	close(ends[0]);
	if (cmd->in_fd == -1 || cmd->out_fd == -1)	
		exit_child(exec, ends[1], *old_end, 1);
	// if (handle_redirection_2(cmd, *old_end, ends[1]) == 1)
	// 	exit_child(exec, ends[1], *old_end, 1);
	if (dup2(ends[1], 1) == -1)
	{
		ft_putendl_fd("FATAL child error 1", 2);
		exit_child(exec, ends[1], *old_end, 1);
	}
	close(ends[1]);
	if (dup2(*old_end, 0) == -1)
	{
		ft_putendl_fd("FATAL child error 2", 2);
		exit_child(exec, *old_end, -1, 1);
	}
	close(*old_end);
	if (exec->paths != NULL)
	{
		cmd->cmd_path = get_cmd_path(exec, cmd);
		if (cmd->cmd_path == NULL)
		exit_child(exec, -1, -1, 1);
	}
	execute_cmd(exec, cmd);
}

void	last_child_proc(t_executor *exec, t_cmd *cmd, int old_end)
{
	// if (handle_redirection(cmd) == 1)
	// 	exit_child(exec, -1, -1, 1);
	if (dup2(old_end, 0) == -1)
	{
		ft_putendl_fd("FATAL child error 3", 2);
		exit_child(exec, old_end, -1, 1);
	}
	close(old_end);
	if (exec->paths != NULL)
	{
		cmd->cmd_path = get_cmd_path(exec, cmd);
		if (cmd->cmd_path == NULL)
			exit_child(exec, -1, -1, 1);
	}
	execute_cmd(exec, cmd);	
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

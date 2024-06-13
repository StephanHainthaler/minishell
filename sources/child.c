/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/13 19:20:47 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	child_proc(t_executor *exec, t_cmd *cmd, int ends[])
{
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit_child(exec, ends[0], ends[1], 1);
	if (handle_redirection(cmd) == 1)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/31 09:15:56 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execute_cmd(t_executor *exec, t_cmd *cmd)
{
	if (cmd->simp_cmd == NULL)
		exit_child(exec, -1, -1, 0);
	if (handle_builtins_1(exec, cmd->simp_cmd) == 0)
		exit_child(exec, -1, -1, exec->exit_status);
	if (handle_builtins_2(exec, cmd->simp_cmd) == 0)
		exit_child(exec, -1, -1, exec->exit_status);
	if (access(cmd->cmd_path, F_OK) != 0)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(exec, -1, -1, 127);
	}
	if (access(cmd->cmd_path, F_OK | X_OK) != 0)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": no permission", 2);
		exit_child(exec, -1, -1, 126);
	}
	if (execve(cmd->cmd_path, cmd->simp_cmd, exec->envp) == -1)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(exec, -1, -1, 127);
	}
}

void	single_child_proc(t_executor *exec, t_cmd *cmd)
{	
	cmd->is_parent = false;
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit_child(exec, -1, -1, 1);
	if (handle_redirection(cmd, 0 ,1) == 1)
		exit_child(exec, -1, -1, 1);
	//if (exec->paths != NULL && cmd->simp_cmd != NULL)
	if (cmd->simp_cmd != NULL)
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
	cmd->is_parent = false;
	close(ends[0]);
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit_child(exec, *old_end, ends[1], 1);
	if (handle_redirection(cmd, *old_end, ends[1]) == 1)
		exit_child(exec, *old_end, ends[1], 1);
	if (dup2(*old_end, 0) == -1)
	{
		ft_putendl_fd("FATAL child error", 2);
		exit_child(exec, *old_end, ends[1], 1);
	}
	close(*old_end);
	if (dup2(ends[1], 1) == -1)
	{
		ft_putendl_fd("FATAL child error", 2);
		exit_child(exec, ends[1], -1, 1);
	}
	close(ends[1]);
	//if (exec->paths != NULL && cmd->simp_cmd != NULL)
	if (cmd->simp_cmd != NULL)
	{
		cmd->cmd_path = get_cmd_path(exec, cmd);
		if (cmd->cmd_path == NULL)
		exit_child(exec, -1, -1, 1);
	}
	execute_cmd(exec, cmd);
}

void	last_child_proc(t_executor *exec, t_cmd *cmd, int old_end)
{
	cmd->is_parent = false;
	if (cmd->in_fd == -1 || cmd->out_fd == -1)	
		exit_child(exec, old_end, -1, 1);
	if (handle_redirection(cmd, old_end, 1) == 1)
		exit_child(exec, old_end, -1, 1);
	if (dup2(old_end, 0) == -1)
	{
		ft_putendl_fd("FATAL child error", 2);
		exit_child(exec, old_end, -1, 1);
	}
	close(old_end);
	if (cmd->simp_cmd != NULL)
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
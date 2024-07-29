/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/29 13:48:37 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execute_cmd(t_executor *exec, t_cmd *cmd)
{
	//printf("%i\n", exec->is_path_set);
	// 	exit_child(exec, -1, -1, 127);
	// if (exec->is_path_set == false)
	// {
	// 	// if (access(cmd->simp_cmd[0], F_OK) == 0)
	// 	// 	printf("cmd exists: %s\n", cmd->simp_cmd[0]);
	// 	// else
	// 	// 	printf("cmd DOES NOT exist: %s\n", cmd->simp_cmd[0]);
	// 	printf("ARGH\n");
	// 	if (execve(cmd->simp_cmd[0], cmd->simp_cmd, exec->envp) == -1)
	// 	{
	// 		ft_putstr_fd(cmd->simp_cmd[0], 2);
	// 		ft_putendl_fd(": command not found", 2);
	// 		exit_child(exec, -1, -1, 127);
	// 	}
	// 	printf("ARGH\n");
	// }
	if (cmd->simp_cmd == NULL)
		exit_child(exec, -1, -1, 0);
	if (handle_builtin(cmd->simp_cmd, exec) == 0)
		exit_child(exec, -1, -1, 0);
	if (execve(cmd->cmd_path, cmd->simp_cmd, exec->envp) == -1)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(exec, -1, -1, 127);
	}
}

void	single_child_proc(t_executor *exec, t_cmd *cmd)
{	
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit_child(exec, -1, -1, 1);
	if (handle_redirection(cmd, 0 ,1) == 1)
		exit_child(exec, -1, -1, 1);
	if (exec->paths != NULL && cmd->simp_cmd != NULL)
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
	if (exec->paths != NULL && cmd->simp_cmd != NULL)
	{
		cmd->cmd_path = get_cmd_path(exec, cmd);
		if (cmd->cmd_path == NULL)
		exit_child(exec, -1, -1, 1);
	}
	execute_cmd(exec, cmd);
}

void	last_child_proc(t_executor *exec, t_cmd *cmd, int old_end)
{
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
	if (exec->paths != NULL && cmd->simp_cmd != NULL)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/13 14:26:12 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	execute_input(t_minishell *ms)
{
	if (initialize_executor_2(ms, 0) == 1)
		return (1);
	if (ms->exec->num_of_cmds == 1)
	{
		if (ms->exec->cmds[0]->in_fd == -1 || ms->exec->cmds[0]->out_fd == -1)
			return (1);
		if (handle_builtins_non_pipable(ms) == 0)
			return (printf("End of cmd\n"), 0);
		if (single_execution(ms->exec) == 1)
			return (1);
	}
	else
	{
		printf("Test multi_pipes\n");
		if (multiple_execution(ms->exec) == 1)
			return (1);
	}
	return (0);
}

int	single_execution(t_executor *exec) //t_minishell *ms
{
	int	status;
	//exit_status;

	exec->cpids[0] = fork();
	if (exec->cpids[0] == -1)
		return (1);
	if (exec->cpids[0] == 0)
		single_child_proc(exec, exec->cmds[0]);
	waitpid(exec->cpids[0], &status, 0);
	//free_exec(exec);
	//change last cmd status in ms
	//exit(WEXITSTATUS(status));
	return (0);
}

int	multiple_execution(t_executor *exec)
{
	int	i;
	int	status;

	i = 0;
	while (i < exec->num_of_pipes)
	{
		printf("Pipe number %d\n", i + 1);
		if (pipe(exec->pipes[i]) == -1)
			return (1);
		exec->cpids[i] = fork();
		if (exec->cpids[i] == -1)
			return (close(exec->pipes[i][0]), close(exec->pipes[i][1]), 1);
		if (exec->cpids[i] == 0)
			child_proc(exec, exec->cmds[i], exec->pipes[i]);
		exec->cpids[i + 1] = fork();
		if (exec->cpids[i + 1] == -1)
			return (close(exec->pipes[i][0]), close(exec->pipes[i][1]), 1);
		if (exec->cpids[i + 1] == 0)
			child_proc(exec, exec->cmds[i + 1], exec->pipes[i]);
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		printf("Waiting...\n");
		waitpid(exec->cpids[i], NULL, 0);
		waitpid(exec->cpids[i + 1], &status, 0);
		printf("End Waiting\n");
		i++;
	}
	return (0);
}

void	execute_cmd(t_executor *exec, t_cmd *cmd)
{
	if (cmd->cmd_path == NULL)
		exit_child(exec, -1, -1, 127);
	if (handle_builtin(cmd->simp_cmd, exec) == 0)
		exit_child(exec, -1, -1, 0);
	if (execve(cmd->cmd_path, cmd->simp_cmd, exec->envp) == -1)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(exec, -1, -1, 127);
	}
}


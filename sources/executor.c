/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/25 14:57:32 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	execute_input(t_minishell *ms)
{
	if (initialize_executor_2(ms) == 1)
		return (1);
	if (ms->exec->cmds[0]->simp_cmd == NULL)
		return (0);
	if (ms->exec->num_of_cmds == 1)
	{
		if (ms->exec->cmds[0]->in_fd == -1 || ms->exec->cmds[0]->out_fd == -1)
			return (free_executor(ms->exec), 2);
		if (handle_builtins_non_pipable(ms) == 0)
			return (0);
		if (single_execution(ms->exec) == 1)
			return (1);
		ms->last_exit_code = ms->exec->exit_status;
		return (0);
	}
	if (multiple_execution(ms->exec) == 1)
		return (1);
	ms->last_exit_code = ms->exec->exit_status;
	return (0);
}

int	single_execution(t_executor *exec)
{
	int		status;
	pid_t	cpid;

	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	cpid = fork();
	if (cpid == -1)
		return (1);
	if (cpid == 0)
		single_child_proc(exec, exec->cmds[0]);
	waitpid(cpid, &status, 0);
	//if (WIFEXITED(status))
	exec->exit_status = WEXITSTATUS(status);
	//free_exec(exec);
	//change last cmd status in ms
	//exit(WEXITSTATUS(status));
	return (0);
}

int	multiple_execution(t_executor *exec)
{
	int	old_end;
	int	i;
	
	old_end = dup(0);
	if (old_end == -1)
		return (1);
	i = 0;
	while (i < exec->num_of_cmds - 1)
	{
		if (multi_pipe(exec, &old_end, i) == 1)
			return (1);
		i++;
	}
	if (last_pipe(exec, old_end, i) == 1)
		return (1);
	return (0);
}

int	multi_pipe(t_executor *exec, int *old_end, int i)
{
	//int		status;
	int		ends[2];
	pid_t	cpid;

	if (pipe(ends) == -1)
		return (1);
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	cpid = fork();
	if (cpid == -1)
		return (1);
	if (cpid == 0)
		multi_child_proc(exec, exec->cmds[i], ends, old_end);
	close(ends[1]);
	close(*old_end);
	*old_end = ends[0];
	// waitpid(cpid, &status, 0);
	// exec->exit_status = WEXITSTATUS(status);
	//printf("Exit Status: %i\n", WEXITSTATUS(status));
	return (0);
}

int	last_pipe(t_executor *exec, int old_end, int i)
{
	int		status;
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
		return (1);
	if (cpid == 0)
		last_child_proc(exec, exec->cmds[i], old_end);
	close(old_end);
	waitpid(cpid, &status, 0);
	exec->exit_status = WEXITSTATUS(status);
	//printf("Exit Status: %i\n", WEXITSTATUS(status));
	return (0);
}


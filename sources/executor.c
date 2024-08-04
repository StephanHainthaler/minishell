/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/31 14:36:00 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Executes the parsed input in mostly child processes.
//<PARAM> The main struct of the program.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	execute_input(t_minishell *ms)
{
	int	error_check;

	if (initialize_executor_2(ms) == 1)
		return (1);
	if (ms->exec->num_of_cmds == 1)
	{
		if (ms->exec->cmds[0]->in_fd == -1 || ms->exec->cmds[0]->out_fd == -1)
			return (free_executor(ms->exec), ms->last_exit_code = 1, 2);
		error_check = handle_builtins_non_pipable(ms, ms->exec->cmds[0]->simp_cmd);
		if (error_check == -1)
			return (ms->last_exit_code = 1, 1);
		if (error_check == 2)
			return (free_executor(ms->exec), ms->last_exit_code = 1, 2);
		if (error_check == 0)
			return (ms->last_exit_code = 0, 0);
		if (single_execution(ms->exec) == 1)
			return (ms->last_exit_code = ms->exec->exit_status, 1);
		return (ms->last_exit_code = ms->exec->exit_status, 0);
	}
	if (multiple_execution(ms->exec) == 1)
		return (ms->last_exit_code = ms->exec->exit_status, 1);
	return (ms->last_exit_code = ms->exec->exit_status, 0);
}

//Forks into a single child process for the execution.
//The parent process waits for its child and its exit status.
//<PARAM> The executor struct.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
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
	if (global_code != 2)
		exec->exit_status = WEXITSTATUS(status);
	else
		exec->exit_status = 130;
	return (0);
}

//Forks into mulitple child processes for the execution.
//The parent process wait for its child and its exit status.
//<PARAM> The executor struct.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
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

//Creates most of the pipeline for the execution.
//It pipes all the commands except the last one.
//<PARAM> The executor struct, the end of the previous pipe & the cmd number.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	multi_pipe(t_executor *exec, int *old_end, int i)
{
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
	return (0);
}

//Creates the end of the pipeline for the execution.
//<PARAM> The executor struct, the end of the previous pipe & the cmd number.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
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
	return (0);
}

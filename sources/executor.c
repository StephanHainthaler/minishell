/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/28 15:06:21 by shaintha         ###   ########.fr       */
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
		printf("Test multi_pipes\n");
		if (multiple_execution(ms->exec) == 1)
			return (1);
	}
	return (0);
}

int	single_execution(t_executor *exec)
{
	int	status;

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

void	execute_cmd(t_executor *exec, t_cmd *cmd)
{
	if (cmd->cmd_path == NULL)
		exit_child(exec, -1, -1, 127);
	if (handle_builtin(cmd->simp_cmd, exec->envp) == 0)
		exit_child(exec, -1, -1, 0);
	if (execve(cmd->cmd_path, cmd->simp_cmd, exec->envp) == -1)
	{
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(exec, -1, -1, 127);
	}
}

int	handle_builtin(char **simp_cmd, char **envp)
{
	printf("ay0\n");
	// if (ft_strncmp(simp_cmd[0], "echo", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (echo(), 0);
	// if (ft_strncmp(simp_cmd[0], "cd", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (cd(), 0);
	// if (ft_strncmp(simp_cmd[0], "pwd", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (pwd(), 0);
	// if (ft_strncmp(simp_cmd[0], "export", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (export(), 0);
	// if (ft_strncmp(simp_cmd[0], "unset", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (unset(), 0);
	if (ft_strncmp(simp_cmd[0], "env", ft_strlen(simp_cmd[0])) == 0)
		return (ft_putstrarr_fd(envp, 1), 0);
	if (ft_strncmp(simp_cmd[0], "exit", ft_strlen(simp_cmd[0])) == 0)
		return (0);
	else
		return (1);
}

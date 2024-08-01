/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/07/31 15:52:36 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//WORK IN PROGRESS - function for child process only PART 2
int	handle_builtins_1(t_executor *exec, char **simp_cmd)
{
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
	//ERROR_HANDLE
		return (ft_cd(simp_cmd, exec->envp), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		exec->envp = ft_export(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (exec->exit_status = 1, 0); // -1 for FATAL ERROR?
		return (exec->exit_status = 0, 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		exec->envp = ft_unset(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (exec->exit_status = 1, 0); // -1 for FATAL ERROR?
		return (exec->exit_status = 0, 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		return (exec->exit_status = get_exitcode(simp_cmd, exec->exit_status), 0);
	return (1);
}

//DONE - function for child process only PART 2
int	handle_builtins_2(t_executor *exec, char **simp_cmd)
{
	if (ft_are_str_indentical(simp_cmd[0], "echo") == true)
		return (ft_echo(simp_cmd), exec->exit_status = 0, 0);
	if (ft_are_str_indentical(simp_cmd[0], "pwd") == true)
	{
		if (ft_pwd() == 1)
			return (exec->exit_status = 1, 0);
		return (exec->exit_status = 0, 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "env") == true)
	{
		if (ft_strarrlen(simp_cmd) > 1)
		{
			ft_putstr_fd("env: '", 2);
			ft_putstr_fd(simp_cmd[1], 2);
			ft_putendl_fd("': No such file or directory", 2);
			return (exec->exit_status = 127, 0);
		}
		ft_putstrarr_fd(exec->envp, 1);
		return (exec->exit_status = 0, 0);
	}
	return (1);
}

//RETURN VALUES:
// 0 == NO BUILT_IN -> nothing happens/continue program
// 1 == FOUND BUILT_IN -> ON SUCCESS -> NEW CYCLE
// 2 == FOUND BUILT_IN -> ON ERROR (non-fatal) -> NEW CYCLE
//-1 == FOUND BUILT_IN -> ON ERROR (FATAL) -> Quit minishell
int	handle_builtins_non_pipable(t_minishell *ms, char **simp_cmd)
{
	if (simp_cmd == NULL)
		return (1);
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
	//ERROR HANDLING
		return (ft_cd(simp_cmd, ms->exec->envp), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		ms->envp = ft_export(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			free_and_exit(ms);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		ms->envp = ft_unset(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			free_and_exit(ms);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		if (ft_exit(ms, simp_cmd) == -1)
			return (0);
	return (1);
}

int	ft_exit(t_minishell *ms, char **simp_cmd)
{
	int	exitcode;

	exitcode = get_exitcode(simp_cmd, ms->last_exit_code);
	if (exitcode == -1)
		return (0);
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
	free_executor(ms->exec);
	rl_clear_history();
	exit(exitcode);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/08/05 10:05:22 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//The first builtin handler for child processes.
//Sets this childs exit code accordingly.
//<PARAM> The executor struct & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND
int	handle_builtins_1(t_executor *exec, char **simp_cmd)
{
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (exec->exit_status = ft_cd(simp_cmd, exec->envp), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		exec->envp = ft_export(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (exec->exit_status = 1, 0);
		return (exec->exit_status = 0, 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		exec->envp = ft_unset(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (exec->exit_status = 1, 0);
		return (exec->exit_status = 0, 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		return (exec->exit_status = get_exitcode(\
			simp_cmd, exec->exit_status), 0);
	return (1);
}

//The second builtin handler for child processes.
//Sets this childs exit code accordingly.
//<PARAM> The executor struct & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND
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

//The builtin handler for the main process.
//Only handles the builtins that cannot be used in a child process.
//<PARAM> The main struct of the program & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND; 2 on standard ERROR; -1 on FATAL ERROR
int	handle_builtins_non_pipable(t_minishell *ms, char **simp_cmd)
{
	if (simp_cmd == NULL)
		return (1);
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (ft_cd(simp_cmd, ms->envp));
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		ms->envp = ft_export(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			return (-1);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		ms->envp = ft_unset(simp_cmd, ms->envp);
		if (ms->envp == NULL)
			return (-1);
		return (0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		if (ft_exit(ms, simp_cmd) == -1)
			return (0);
	return (1);
}

//Exits the main process after freeing allocated memory.
//Only ends the program on non-ERROR.
//<PARAM> The main struct of the program & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on standard ERROR
int	ft_exit(t_minishell *ms, char **simp_cmd)
{
	int	exitcode;

	exitcode = get_exitcode(simp_cmd, ms->last_exit_code);
	if (exitcode == -1)
		return (1);
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
	free_executor(ms->exec);
	rl_clear_history();
	exit(exitcode);
	return (0);
}

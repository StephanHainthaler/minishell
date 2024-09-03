/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/08/13 11:58:02 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//The first builtin handler for child processes.
//Sets this childs exit code accordingly.
//<PARAM> The executor struct & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND;
//<RETURN> 2 on standard ERROR; -1 on FATAL ERROR
int	handle_builtins_1(t_executor *exec, char **simp_cmd)
{
	int	error_check;

	if (ft_is_same(simp_cmd[0], "exit") == true)
		return (exec->exit_status = get_exitcode(\
			simp_cmd, exec->exit_status), 0);
	if (ft_is_same(simp_cmd[0], "env") == true)
		return (ft_env(simp_cmd, exec->envp, exec), 0);
	if (ft_is_same(simp_cmd[0], "echo") == true)
		return (ft_echo(simp_cmd, exec), 0);
	if (ft_is_same(simp_cmd[0], "cd") == true)
		return (error_check = ft_cd(simp_cmd, exec->envp, exec),
			error_check);
	return (1);
}

//The second builtin handler for child processes.
//Sets this childs exit code accordingly.
//<PARAM> The executor struct & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND; -1 on FATAL ERROR
int	handle_builtins_2(t_executor *exec, char **simp_cmd)
{
	if (ft_is_same(simp_cmd[0], "pwd") == true)
	{
		if (ft_pwd(exec) == 1)
			return (-1);
		return (0);
	}
	if (ft_is_same(simp_cmd[0], "export") == true)
	{
		exec->envp = ft_export(simp_cmd, exec->envp, exec, 0);
		if (exec->envp == NULL)
			return (-1);
		return (0);
	}
	if (ft_is_same(simp_cmd[0], "unset") == true)
	{
		exec->envp = ft_unset(simp_cmd, exec->envp, exec, 1);
		if (exec->envp == NULL)
			return (-1);
		return (0);
	}
	return (1);
}

//The builtin handler for the main process.
//Only handles the builtins that cannot be used in a child process.
//<PARAM> The main struct of the program & the current simple command.
//<RETURN> 0 on SUCCESS; 1 on NOT FOUND; 
//<RETURN> 2 on standard ERROR; -1 on FATAL ERROR
int	handle_builtins_non_pipable(t_minishell *ms, char **simp_cmd)
{
	int	error_check;

	if (simp_cmd == NULL)
		return (1);
	if (ft_is_same(simp_cmd[0], "cd") == true)
		return (error_check = ft_cd(simp_cmd, ms->envp, ms->exec),
			ms->last_exit_code = ms->exec->exit_status, error_check);
	if (ft_is_same(simp_cmd[0], "export") == true)
	{
		ms->envp = ft_export(simp_cmd, ms->envp, ms->exec, 0);
		if (ms->envp == NULL)
			return (-1);
		return (ms->last_exit_code = ms->exec->exit_status, 0);
	}
	if (ft_is_same(simp_cmd[0], "unset") == true)
	{
		ms->envp = ft_unset(simp_cmd, ms->envp, ms->exec, 1);
		if (ms->envp == NULL)
			return (-1);
		return (ms->last_exit_code = ms->exec->exit_status, 0);
	}
	if (ft_is_same(simp_cmd[0], "exit") == true)
		if (ft_exit(ms, simp_cmd) == 2)
			return (ms->last_exit_code = ms->exec->exit_status, 2);
	return (1);
}

//Exits the main process after freeing allocated memory.
//Only ends the program on non-ERROR.
//<PARAM> The main struct of the program & the current simple command.
//<RETURN> 0 on SUCCESS; 2 on standard ERROR
int	ft_exit(t_minishell *ms, char **simp_cmd)
{
	int	exitcode;

	exitcode = get_exitcode(simp_cmd, ms->last_exit_code);
	if (exitcode == -1)
		return (ms->exec->exit_status = 1, 2);
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
	free_executor(ms->exec);
	rl_clear_history();
	printf("exit\n");
	exit(exitcode);
	return (0);
}

//Replicates the command env with no options.
//Flags are not implemented.
//Changes the exit status depending on the outcome.
//<PARAM> The current simple command, the environment pointers &
//<PARAM> the executor struct.
//<RETURN> void
void	ft_env(char **simp_cmd, char **envp, t_executor *exec)
{
	size_t	i;

	if (ft_strarrlen(simp_cmd) > 1)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(simp_cmd[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		exec->exit_status = 127;
		return ;
	}
	i = 0;
	while (i < ft_strarrlen(envp))
	{
		if (ft_strchr(envp[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		else
			printf("%s\n", envp[i]);
		i++;
	}
	exec->exit_status = 0;
}

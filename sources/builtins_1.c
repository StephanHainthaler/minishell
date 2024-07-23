/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/07/23 14:29:17 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <string.h>

int	handle_builtin(char **simp_cmd, t_executor *exec)
{
	if (ft_are_str_indentical(simp_cmd[0], "echo") == true)
		return (ft_echo(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (ft_cd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "pwd") == true)
		return (ft_pwd(simp_cmd), 0);
	if (ft_are_str_indentical(simp_cmd[0], "export") == true)
	{
		exec->envp = ft_export(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (-1);
		return (ft_export(simp_cmd, exec->envp), 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "unset") == true)
	{
		exec->envp = ft_unset(simp_cmd, exec->envp);
		if (exec->envp == NULL)
			return (-1);
		return (ft_unset(simp_cmd, exec->envp), 0);
	}
	if (ft_are_str_indentical(simp_cmd[0], "env") == true)
		return (ft_putstrarr_fd(exec->envp, 1), 0);
	if (ft_are_str_indentical(simp_cmd[0], "exit") == true)
		return (0);
	return (1);
}

int	handle_builtins_non_pipable(t_minishell *ms)
{
	char **simp_cmd;

	simp_cmd = ms->exec->cmds[0]->simp_cmd;
	if (ft_are_str_indentical(simp_cmd[0], "cd") == true)
		return (ft_cd(simp_cmd), 0);
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
		free_and_exit(ms);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:52:39 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/17 09:53:57 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[])
{
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = ft_strarrdup(env);
	if (ms->envp == NULL)
		return (1);
	ms->lex = NULL;
	ms->exec = NULL;
	ms->last_exit_code = 0;
	return (0);
}

int	initialize_lexer(t_minishell *ms)
{
	ms->lex = (t_lexer *)malloc(sizeof(t_lexer));
	if (ms->lex == NULL)
		return (1);
	ms->lex->token_list = NULL;
	ms->lex->input = NULL;
	ms->lex->i = 0;
	ms->lex->envp = ms->envp;
	return (0);
}

int	initialize_executor(t_minishell *ms)
{
	int	i;

	ms->exec = (t_executor *)malloc(sizeof(t_executor));
	if (ms->exec == NULL)
		return (1);
	ms->exec->num_of_cmds = count_cmds(&ms->lex->token_list);
	ms->exec->num_of_pipes = ms->exec->num_of_cmds - 1;
	ms->exec->cmds = (t_cmd **)malloc(ms->exec->num_of_cmds * sizeof(t_cmd *));
	if (ms->exec->cmds == NULL)
		return (free(ms->exec), 1);
	i = 0;
	while (i < ms->exec->num_of_cmds)
	{
		ms->exec->cmds[i] = initialize_cmd(ms->exec->cmds[i], i);
		if (ms->exec->cmds[i] == NULL)
			return (free_cmds(ms->exec->cmds, i), free(ms->exec), 1);
		i++;
	}
	ms->exec->paths = NULL;
	ms->exec->pipes = NULL;
	ms->exec->cpids = NULL;
	ms->exec->envp = ms->envp;
	return (0);
}

int	initialize_executor_2(t_minishell *ms, int i)
{
	int	error_flag;

	error_flag = 0;
	ms->exec->cpids = (pid_t *)malloc(ms->exec->num_of_cmds * sizeof(pid_t));
	if (ms->exec->cpids == NULL)
		return (1);
	ms->exec->pipes = (int **)malloc(ms->exec->num_of_pipes * sizeof(int *));
	if (ms->exec->pipes == NULL)
		return (free(ms->exec->cpids), 1);
	while (i < ms->exec->num_of_pipes)
	{
		ms->exec->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (ms->exec->pipes[i] == NULL)
			return (free_pipes(ms->exec->pipes, i), 1);
		ms->exec->pipes[i][0] = -1;
		ms->exec->pipes[i][1] = -1;
		i++;
	}
	if (is_path_set(ms->envp) == true)
	{
		ms->exec->paths = get_paths(ms->exec, &error_flag);
		if (ms->exec->paths == NULL && error_flag == 1)
			return (free(ms->exec->cpids), free_pipes(ms->exec->pipes, i), 1);
	}
	return (0);
}

t_cmd	*initialize_cmd(t_cmd *cmd, int cmd_nbr)
{	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->simp_cmd = NULL;
	cmd->cmd_path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->here_doc = NULL;
	cmd->in_fd = 0;
	cmd->out_fd = 1;
	cmd->cmd_nbr = cmd_nbr;
    return (cmd);
}

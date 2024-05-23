/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:52:39 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/23 09:37:55 by shaintha         ###   ########.fr       */
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

int	initialize_cmd(t_cmd *cmd, int cmd_nbr)
{	
	cmd->simp_cmd = NULL;
	cmd->cmd_path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->in_fd = 0;
	cmd->out_fd = 1;
	cmd->cmd_nbr = cmd_nbr;
    return (0);
}

int	initialize_executor(t_minishell *ms)
{
	ms->exec = (t_executor *)malloc(sizeof(t_executor));
	if (ms->exec == NULL)
		return (1);
	ms->exec->cmds = (t_cmd **)malloc(ms->exec->num_of_cmds * sizeof(t_cmd *));
	if (ms->exec->cmds == NULL)
		return (free(ms->exec), 1);
	ms->exec->paths = NULL;
	ms->exec->pipes = NULL;
	ms->exec->cpids = NULL;
	ms->exec->envp = ms->envp;
	return (0);
}

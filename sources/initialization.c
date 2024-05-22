/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:52:39 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/22 15:20:29 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[])
{
	ms->num_of_cmds = 0;
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = ft_strarrdup(env);
	if (ms->envp == NULL)
		return (1);
	return (0);
}

int	initialize_lexer(t_minishell *ms)
{
	ms->lex = (t_lexer *)malloc(sizeof(t_lexer));
	if (ms->lex == NULL)
		return (1);
	ms->lex->token_list = NULL;
	ms->lex->input = NULL;
	ms->lex->envp = ms->envp;
	return (0);
}

int    initialize_cmd(t_cmd *cmd, int cmd_nbr)
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

int	initialize_parser(t_minishell *ms)
{
	ms->cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	if (ms->cmds == NULL)
		return (1);
	//init all other cmd values
	return (0);
}

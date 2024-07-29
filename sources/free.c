/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/29 15:33:23 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_lexer(t_lexer *lex)
{
	if (lex == NULL)
		return ;
	if (lex->token_list != NULL)
		ft_lstclear(&lex->token_list);
	if (lex->input != NULL)
		free(lex->input);
	free(lex);
	lex = NULL;
}

void	free_executor(t_executor *exec)
{
	if (exec == NULL)
		return ;
	if (exec->paths != NULL)
		ft_free_strarr(exec->paths);
	free_cmds(exec->cmds, exec->num_of_cmds);
	free(exec);
	exec = NULL;
}

void	free_cmds(t_cmd **cmds, int num_of_cmds)
{
	int	i;

	i = 0;
	if (cmds == NULL)
		return ;
	while (i < num_of_cmds)
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd_path != NULL)
		free(cmd->cmd_path);
	if (cmd->infile != NULL)
		free(cmd->infile);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	if (cmd->in_fd != 0 && cmd->in_fd != -1)
		close(cmd->in_fd);
	if (cmd->out_fd != 1 && cmd->out_fd != -1)
		close(cmd->out_fd);
	if (cmd->simp_cmd != NULL)
		ft_free_strarr(cmd->simp_cmd);
	if (cmd->has_here_doc == true)
		unlink(cmd->here_doc);
	if (cmd->here_doc != NULL)
		free(cmd->here_doc);
	free(cmd);
	cmd = NULL;
}

void	free_and_exit(t_minishell *ms)
{
	// int	exitcode;

	// exitcode = get_exitcode(simp_cmd);
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
	free_executor(ms->exec);
	rl_clear_history();
	//exit(global_code);
	exit(0);
}

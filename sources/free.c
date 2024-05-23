/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/23 12:48:08 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_minishell(t_minishell *ms)
{
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
}

void	free_lexer(t_lexer *lex)
{
	if (lex->token_list != NULL)
		ft_lstclear(&lex->token_list);
	free(lex);
}

void	free_and_exit(t_minishell *ms)
{
	free_lexer(ms->lex);
	free_minishell(ms);
	rl_clear_history();
	exit(0);
}

void	free_executor(t_executor *exec)
{
	if (exec == NULL)
		return ;
	free_cmds(exec->cmds, exec->num_of_cmds);
	//	exec->paths = NULL;
	//	exec->pipes = NULL;
	//	exec->cpids = NULL;
	//	exec->envp = ms->envp;
	free(exec);
}

void	free_cmds(t_cmd **cmds, int	num_of_cmds)
{
	int	i;

	i = 0;
	if (cmds == NULL)
		return ;
	while (i < num_of_cmds)
	{
		if (cmds[i]->simp_cmd != NULL)
			ft_free_strarr(cmds[i]->simp_cmd);
		if (cmds[i]->cmd_path != NULL)
			free(cmds[i]->cmd_path);
		if (cmds[i]->infile != NULL)
			free(cmds[i]->infile);
		if (cmds[i]->outfile != NULL)
			free(cmds[i]->outfile);
		if (cmds[i]->in_fd != 0 && cmds[i]->in_fd != -1)
			close(cmds[i]->in_fd);
		if (cmds[i]->out_fd != 1 && cmds[i]->out_fd != -1)
			close(cmds[i]->out_fd);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/27 13:40:43 by shaintha         ###   ########.fr       */
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
	if (lex == NULL)
		return ;
	if (lex->token_list != NULL)
		ft_lstclear(&lex->token_list);
	free(lex);
}

void	free_executor(t_executor *exec)
{
	if (exec == NULL)
		return ;
	if (exec->paths != NULL)
		ft_free_strarr(exec->paths);
	if (exec->cpids != NULL)
		free(exec->cpids);
	if (exec->pipes != NULL)
		free(exec->pipes);
	free_cmds(exec->cmds, exec->num_of_cmds);
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
		printf("Free test: 0\n");
		if (cmds[i]->simp_cmd != NULL)
		{
			printf("Free test: 1\n");
			ft_free_strarr(cmds[i]->simp_cmd);
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_and_exit(t_minishell *ms)
{
	free_lexer(ms->lex);
	free_minishell(ms);
	rl_clear_history();
	exit(0);
}

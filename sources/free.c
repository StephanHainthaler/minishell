/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/18 16:10:17 by shaintha         ###   ########.fr       */
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
	// if (exec->cpids != NULL)
	// 	free(exec->cpids);
	// if (exec->pipes != NULL)
	// 	free_pipes(exec->pipes, exec->num_of_pipes);
	free_cmds(exec->cmds, exec->num_of_cmds);
	free(exec);
	exec = NULL;
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
		if (cmds[i]->simp_cmd != NULL)
			ft_free_strarr(cmds[i]->simp_cmd);
		if (cmds[i]->has_here_doc == true)
			//unlink("temp");
			unlink(cmds[i]->here_doc);
		if (cmds[i]->here_doc != NULL)
			free(cmds[i]->here_doc);
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	free_and_exit(t_minishell *ms) //int exit_code
{
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
	free_executor(ms->exec);
	rl_clear_history();
	exit(0);
}

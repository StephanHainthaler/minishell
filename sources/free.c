/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/05 10:23:30 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Frees the allocated memory for the lexer struct.
//<PARAM> The lexer to be freed.
//<RETURN> void
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

//Frees the allocated memory for the executor struct.
//<PARAM> The executor to be freed.
//<RETURN> void
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

//Frees the allocated memory for all cmd structs.
//<PARAM> The cmds to be freed & the total amount of cmds.
//<RETURN> void
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

//Frees the allocated memory for a single cmd struct.
//<PARAM> The cmd to be freed.
//<RETURN> void
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
	if (cmd->has_here_doc == true && cmd->is_parent == true)
		unlink(cmd->here_doc);
	if (cmd->here_doc != NULL)
		free(cmd->here_doc);
	free(cmd);
	cmd = NULL;
}

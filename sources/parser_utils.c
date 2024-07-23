/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/23 14:34:30 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

int	get_word(t_executor *exec, char *word, int i)
{
	exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, word);
	if (exec->cmds[i]->simp_cmd == NULL)
		return (1);
	return (0);
}

int	get_outfile_redir(t_executor *exec, char *outfile, t_type type, int i)
{
	if (exec->cmds[i]->outfile != NULL)
		free(exec->cmds[i]->outfile);
	if (exec->cmds[i]->out_fd != -1 && exec->cmds[i]->out_fd != 1)
		close(exec->cmds[i]->out_fd);
	exec->cmds[i]->outfile = ft_strdup(outfile);
	if (exec->cmds[i]->outfile == NULL)
		return (1);
	if (type == RE_OUT)
		exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false, false);
	else
		exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false, true);
	return (0);
}

int	get_infile_redir(t_executor *exec, char *infile, int i)
{
	if (exec->cmds[i]->infile != NULL)
		free(exec->cmds[i]->infile);
	if (exec->cmds[i]->in_fd != -1 && exec->cmds[i]->in_fd != 0)
		close(exec->cmds[i]->in_fd);
	if (exec->cmds[i]->has_here_doc == true)
		unlink(exec->cmds[i]->here_doc);
	exec->cmds[i]->has_here_doc = false;
	exec->cmds[i]->infile = ft_strdup(infile);
	if (exec->cmds[i]->infile == NULL)
		return (1);
	exec->cmds[i]->in_fd = get_fd(exec->cmds[i]->infile, true, false);
	return (0);
}

int	get_here_doc(t_executor *exec, char *delim, int i)
{
	int	error_check;

	if (exec->cmds[i]->infile != NULL)
		free(exec->cmds[i]->infile);
	if (exec->cmds[i]->in_fd != -1 && exec->cmds[i]->in_fd != 0)
		close(exec->cmds[i]->in_fd);
	if (exec->cmds[i]->has_here_doc == true)
		unlink(exec->cmds[i]->here_doc);
	exec->cmds[i]->has_here_doc = true;
	exec->cmds[i]->infile = ft_strdup(exec->cmds[i]->here_doc);
	if (exec->cmds[i]->infile == NULL)
		return (1);
	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (exec->cmds[i]->in_fd == -1)
		return (1);
	error_check = handle_here_doc(exec->cmds[i]->in_fd, delim, \
		exec->envp, exec->exit_status);
	if (error_check == 1 || error_check == 2)
		return (error_check);
	close(exec->cmds[i]->in_fd);
	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_RDONLY, 0777);
	if (exec->cmds[i]->in_fd == -1)
		return (1);
	return (0);
}

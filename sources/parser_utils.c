/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:34:30 by juitz             #+#    #+#             */
/*   Updated: 2024/08/13 11:01:26 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Stores a new word token in the current command struct.
//In case of containing quotes, the word token will be dequoted.
//<PARAM> The executor struct, the new word token & the current cmd number.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	get_word(t_executor *exec, char *word, size_t i)
{
	char	*deq_word;

	if (ft_strchr(word, '\'') || ft_strchr(word, '"'))
	{
		deq_word = NULL;
		deq_word = dequote(word);
		if (deq_word == NULL)
			return (1);
		exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(\
			exec->cmds[i]->simp_cmd, deq_word);
		if (exec->cmds[i]->simp_cmd == NULL)
			return (free(deq_word), 1);
		return (free(deq_word), 0);
	}
	exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, word);
	if (exec->cmds[i]->simp_cmd == NULL)
		return (1);
	return (0);
}

//Stores a new outfile token in the current command struct.
//The mode of the out will depend on the given type.
//In case of containing quotes, the out token will be dequoted.
//<PARAM> The executor struct, the new out token, 
//<PARAM> the type of out & the current cmd number.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	get_outfile_redir(t_executor *exec, char *outfile, t_type type, size_t i)
{
	if (exec->cmds[i]->outfile != NULL)
		free(exec->cmds[i]->outfile);
	if (exec->cmds[i]->out_fd != -1 && exec->cmds[i]->out_fd != 1)
		close(exec->cmds[i]->out_fd);
	if (is_file_ambigious(outfile) == true)
		return (2);
	if (ft_strchr(outfile, '\'') || ft_strchr(outfile, '"'))
		exec->cmds[i]->outfile = dequote(outfile);
	else
		exec->cmds[i]->outfile = ft_strdup(outfile);
	if (exec->cmds[i]->outfile == NULL)
		return (1);
	if (type == RE_OUT)
		exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false, false);
	else
		exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false, true);
	return (0);
}

//Stores a new infile token in the current command struct.
//In case of containing quotes, the out token will be dequoted.
//<PARAM> The executor struct, the new in token & the current cmd number.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	get_infile_redir(t_executor *exec, char *infile, size_t i)
{
	if (exec->cmds[i]->infile != NULL)
		free(exec->cmds[i]->infile);
	if (exec->cmds[i]->in_fd != -1 && exec->cmds[i]->in_fd != 0)
		close(exec->cmds[i]->in_fd);
	if (exec->cmds[i]->has_here_doc == true)
		unlink(exec->cmds[i]->here_doc);
	exec->cmds[i]->has_here_doc = false;
	if (is_file_ambigious(infile) == true)
		return (2);
	if (ft_strchr(infile, '\'') || ft_strchr(infile, '"'))
		exec->cmds[i]->infile = dequote(infile);
	else
		exec->cmds[i]->infile = ft_strdup(infile);
	if (exec->cmds[i]->infile == NULL)
		return (1);
	exec->cmds[i]->in_fd = get_fd(exec->cmds[i]->infile, true, false);
	return (0);
}

//Stores a new here_doc token in the current command struct.
//Creates a temporary infile in the directory for redirection.
//<PARAM> The executor struct, the delimiter & the current cmd number.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	get_here_doc(t_executor *exec, char *delim, size_t i)
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
	exec->cmds[i]->in_fd = open(\
		exec->cmds[i]->here_doc, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (exec->cmds[i]->in_fd == -1)
		return (1);
	error_check = handle_here_doc(exec->cmds[i]->in_fd, delim, exec);
	if (error_check == 1 || error_check == 2 || error_check == 3)
		return (error_check);
	close(exec->cmds[i]->in_fd);
	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_RDONLY, 0777);
	if (exec->cmds[i]->in_fd == -1)
		return (1);
	return (0);
}

//Checks if the redirection for the in/outfile is ambigious.
//<PARAM> The file to be checked.
//<RETURN> bool
bool	is_file_ambigious(char *file)
{
	char	quote;
	size_t	i;

	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\'' || file[i] == '"')
		{
			quote = file[i++];
			while (file[i] != quote)
				i++;
		}
		if (ft_isspace(file[i]) == true)
		{
			ft_putstr_fd("exec: ", 2);
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": ambiguous redirect", 2);
			return (true);
		}
		i++;
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/07/25 13:25:01 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	parse_input(t_minishell *ms)
{
	int	error_check;

	if (initialize_executor(ms) == 1)
		return (1);
	if (is_valid_input(ms->lex) == false)
		return (free_lexer(ms->lex), free_executor(ms->exec), 2);
	error_check = get_cmds(ms->exec, &ms->lex->token_list, 0, 0);
	if (error_check == 1)
		return (free_executor(ms->exec), 1);
	if (error_check == 2)
		return (free_executor(ms->exec), free_lexer(ms->lex), 2);
	return (0);
}

int	get_cmds(t_executor *exec, t_list **list, int error_check, int i)
{
	t_list	*cur;

	cur = *list;
	while (cur)
	{
		if (cur->type == WORD)
			error_check = get_word(exec, cur->attr, i);
		if (cur->type != WORD && cur->type != PIPE)
		{
			if (cur->type == RE_IN)
				error_check = get_infile_redir(exec, cur->next->attr, i);
			if (cur->type == RE_OUT || cur->type == APPEND)
				error_check = get_outfile_redir(exec, cur->next->attr, \
					cur->type, i);
			if (cur->type == HERE_DOC)
				error_check = get_here_doc(exec, cur->next->attr, i);
			cur = cur->next;
		}
		if (error_check == 1 || error_check == 2)
			return (error_check);
		if (cur->type == PIPE)
			i++;
		cur = cur->next;
	}
	return (0);
}

int	count_cmds(t_list **list)
{
	t_list	*current_node;
	int		num_of_cmds;

	current_node = *list;
	num_of_cmds = 1;
	while (current_node != NULL)
	{
		if (current_node->type == PIPE)
			num_of_cmds++;
		current_node = current_node->next;
	}
	return (num_of_cmds);
}

bool	is_valid_input(t_lexer *lex)
{
	t_list	*cur;
	int		i;

	i = 0;
	cur = lex->token_list;
	while (cur != NULL)
	{
		if (cur->type == PIPE && i == 0)
			return (ft_putendl_fd("input can not start with `|'", 2), false);
		if (cur->type == PIPE && cur->next->type == PIPE)
			return (ft_putendl_fd("no double pipes allowed in here", 2), false);
		if (cur->type == RE_IN && cur->next != NULL && cur->next->type != WORD)
			return (ft_putendl_fd("parse error near `<'", 2), false);
		if (cur->type == RE_OUT && cur->next != NULL && cur->next->type != WORD)
			return (ft_putendl_fd("parse error near `>'", 2), false);
		if (cur->type == 5 && cur->next != NULL && cur->next->type != WORD)
			return (ft_putendl_fd("parse error near `<<'", 2), false);
		if (cur->type == APPEND && cur->next != NULL && cur->next->type != WORD)
			return (ft_putendl_fd("parse error near `>>'", 2), false);
		if (cur->type != WORD && cur->next == NULL)
			return (ft_putendl_fd("last input is not word token", 2), false);
		cur = cur->next;
		i++;
	}
	return (true);
}

void	ft_print_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (i < ft_strarrlen(cmd->simp_cmd))
	{
		printf("cmd->simp_cmd[%zu]: %s\n", i, cmd->simp_cmd[i]);
		i++;
	}
	printf("cmd->infile: %s\n", cmd->infile);
	printf("cmd->outfile: %s\n", cmd->outfile);
	printf("cmd->in_fd: %d\n", cmd->in_fd);
	printf("cmd->out_fd: %d\n", cmd->out_fd);
	printf("cmd->cmd_nbr: %d\n", cmd->cmd_nbr);
	printf("cmd->cmd_path: %s\n", cmd->cmd_path);
}

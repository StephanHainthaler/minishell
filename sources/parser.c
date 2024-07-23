/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/23 14:16:11 by juitz            ###   ########.fr       */
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
	error_check = get_cmds(ms->exec, &ms->lex->token_list, 0 , 0);
	if (error_check == 1)
		return (free_executor(ms->exec), 1);
	if (error_check == 2)
		return (free_executor(ms->exec), free_lexer(ms->lex), 2);
	// i = 0;
	// while (i < ms->exec->num_of_cmds)
	// 	ft_print_cmd(ms->exec->cmds[i++]);
	// printf("\n");
	return (0);
}

int		get_cmds(t_executor *exec, t_list **list, int error_check, int i)
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
				error_check = get_outfile_redir(exec, cur->next->attr, cur->type, i);
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

bool is_valid_input(t_lexer *lex)
{
	t_list *current;
	int		i;

	i = 0;
	current = lex->token_list;
	while (current != NULL)
	{
		if (current->type != WORD && current->next == NULL)
			return (ft_putendl_fd("word token required as last input", 2), false);
		if (current->type == PIPE && i == 0)
			return (ft_putendl_fd("input can not start with `|'", 2), false);
		if (current->type == PIPE && current->next->type == PIPE)
			return (ft_putendl_fd("sorry, no double pipes allowed in here", 2), false);
		if (current->type == RE_IN && current->next != NULL && current->next->type != WORD)
			return (ft_putendl_fd("parse error near `<'", 2), false);
		if (current->type == RE_OUT && current->next != NULL && current->next->type != WORD)
			return (ft_putendl_fd("parse error near `>'", 2), false);
		if (current->type == HERE_DOC && current->next != NULL && current->next->type != WORD)
			return (ft_putendl_fd("parse error near `<<'", 2), false);
		if (current->type == APPEND && current->next != NULL && current->next->type != WORD)
			return (ft_putendl_fd("parse error near `>>'", 2), false);
		current = current->next;
		i++;
	}
	return (true);
}
	// if (current->type == WORD)
		// 	has_wrd = true;
		// if (current->type == PIPE)
		// 	has_wrd = false;
		// if (current->type != PIPE && has_wrd == false)
		// 	return (ft_putendl_fd("command has no word", 2), false);

			// if (has_wrd == false)
	// 	return (ft_putendl_fd("command has no word", 2), false);
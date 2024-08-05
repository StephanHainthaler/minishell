/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/08/05 09:45:55 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Takes the input and converts it to be usable for the executor.
//The information and memory will be stored in the executor struct.
//<PARAM> The main struct of the program.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	parse_input(t_minishell *ms)
{
	int	error_check;

	if (initialize_executor(ms) == 1)
		return (1);
	if (is_valid_input(ms->lex) == false)
		return (ms->last_exit_code = 2, free_lexer(ms->lex),
			free_executor(ms->exec), 2);
	error_check = get_cmds(ms->exec, &ms->lex->token_list, 0, 0);
	if (error_check == 1)
		return (free_executor(ms->exec), 1);
	if (error_check == 2)
		return (ms->last_exit_code = 1, free_lexer(ms->lex),
			free_executor(ms->exec), 2);
	return (0);
}

//Reads the entire linked list and counts the total amount of commands.
//<PARAM> The executor struct, the list, an error indicator & an iterator at 0
//<RETURN> total number of cmds on SUCCESS
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

//Checks the entire list for allowed order of tokens.
//<PARAM> The lexer struct
//<RETURN> bool
bool	is_valid_input(t_lexer *lex)
{
	t_list	*cur;
	int		i;

	i = 0;
	cur = lex->token_list;
	while (cur != NULL)
	{
		if (cur->type != WORD && cur->next == NULL)
			return (ft_putendl_fd("last input is not word token", 2), false);
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
		cur = cur->next;
		i++;
	}
	return (true);
}

//Converts every node of the linked list into a command struct.
//<PARAM> The executor struct, the list, an error indicator & an iterator at 0
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
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

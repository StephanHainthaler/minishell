/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/23 12:53:09 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	parse_input(t_minishell *ms)
{
	if (initialize_executor(ms) == 1)
		return (1);
	// if (get_cmds(ms->exec, &ms->lex->token_list) == 1)
	// 	return (free_executor(ms->exec), 1);
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

// int	get_cmds(t_executor *exec, t_list **list)
// {

// 	t_list	*current;
// 	//bool	has_wrd;
// 	int 	i;

// 	printf("Number of cmds: %d\n", exec->num_of_cmds);
// 	i = 0;
// 	current = *list;
// 	printf("test0\n");
// 	while (current && current->next) //&& i < ms->cmds->num_of_simp_cmds + 1)
// 	{
// 		//exec->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
// 		initialize_cmd(exec->cmds[i], i);
// 		//NULL CHECK
// 		// cmds->simp_cmd = malloc(sizeof(char *) * (ms->cmds->num_of_args + 1));
// 		// if (!cmds->simp_cmd)
// 		// 	return (NULL);
// 		//has_wrd = false;
// 		while (current->next != NULL && current->type != PIPE)
// 		{
// 			if (current->type == WORD)
// 			{
// 				has_wrd = true;
// 				ms->cmds[i]->simp_cmd = ft_stradd_tostrarr(ms->cmds[i]->simp_cmd, current->attr);
// 				if (!ms->cmds)
// 					return (1); //free)
// 				ft_putstrarr_fd(ms->cmds[i]->simp_cmd, 1);
// 			}
// 			// else if (current->type == RE_IN)
// 			// 	ms->cmd->infile = current->next->attr;
// 			// else if (current->type == RE_OUT)
// 			// 	ms->cmd->outfile = current->next->attr;
// 			//NULL CHECK
// 			current = current->next;
// 		}
// 		current = current->next;
// 		i++;
// 	}
// 	// if (has_wrd == false)
// 	// 	return (ft_error("parse error: need at least one word"), 1);
// 	return (0);
// }



// bool is_valid_input(t_lexer *lex)
// {
// 	t_list *head;
// 	t_list *current;

// 	head = lex->token_list;
// 	current = lex->token_list;
// 	while (current != NULL)
// 	{
// 		if (current->type == RE_IN && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `<'"), false);
// 		if (current->type == RE_OUT && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `>'"), false);
// 		if (current->type == HERE_DOC && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `<<'"), false);
// 		if (current->type == APPEND && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `>>'"), false);
// 		if (current->type != WORD && current->next == NULL)
// 			return (ft_error("word token required as last input"), false);
// 		current = current->next;
// 	}
// 	lex->token_list = head;
// 	return (true);
// }
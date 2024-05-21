/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/21 16:00:49 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"



int	count_pipes(t_minishell *ms)
{
	t_list *current;

	current = ms->lex->token_list;
	while (current != NULL)
	{
		if (ms->lex->token_list->type == PIPE)
			ms->num_of_cmds++;
		current = current->next;
	}
	ms->lex->token_list = current;
	return (ms->num_of_cmds + 1);
}
// int	num_of_args(t_minishell *ms)
// {
// 	t_list *current;

// 	current = ms->lex->token_list;
// 	while (current != NULL)
// 	{
// 		if (current->type == WORD)
// 			ms->cmds->num_of_args++;
// 		current = current->next;
// 	}
// 	ms->lex->token_list = current;
// 	return (ms->cmds->num_of_args);
// }

t_cmd	**get_cmds(t_minishell *ms)
{
	t_cmd	**cmds;
	t_cmd	*new_cmd;
	t_list	*current;
	//int cmd_nr[ms->cmds->num_of_simp_cmds + 1];
	int i;
	int j;

	ms->cmds = (t_cmd **)malloc(ms->num_of_cmds * sizeof(t_cmd *));
	if (ms->cmds == NULL)
		return (NULL);
	i = 0;
	current = ms->lex->token_list;
	while (current) //&& i < ms->cmds->num_of_simp_cmds + 1)
	{
		cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
		//NULL CHECK
		// cmds->simp_cmd = malloc(sizeof(char *) * (ms->cmds->num_of_args + 1));
		// if (!cmds->simp_cmd)
		// 	return (NULL);
		while (current->type != PIPE)
		{
			if (current->type == WORD)
				ft_stradd_tostrarr(cmds[i]->simp_cmd, current->attr);
			else if (current->type == RE_IN)
				ms->cmd->infile = current->next->attr;
			else if (current->type == RE_OUT)
				ms->cmd->outfile = current->next->attr;
			//NULL CHECK
			//else if (current->type == RE_IN && current->next->type == WORD)
			current = current->next;
		} 
		current = current->next;
		//cmd_nr[i] = i;
		i++;
	}
	return (cmds);
}
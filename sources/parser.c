/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/20 16:11:39 by juitz            ###   ########.fr       */
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
			ms->cmd->num_of_simp_cmds++;
		current = current->next;
	}
	ms->lex->token_list = current;
	return (ms->cmd->num_of_simp_cmds + 1);
}


t_cmd	*new_cmd(t_minishell *ms)
{
	t_cmd	*new_cmd;
	t_list	*current;
	int i;

	i = 0;
	current = ms->lex->token_list;
	while (current)
	{
		while (i < ms->cmd->num_of_simp_cmds + 1)
		{
		
		}
	}
}
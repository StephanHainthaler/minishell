/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/21 13:50:41 by juitz            ###   ########.fr       */
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
int	num_of_args(t_minishell *ms)
{
	t_list *current;

	current = ms->lex->token_list;
	while (current != NULL)
	{
		if (current->type == WORD)
			ms->cmd->num_of_args++;
		current = current->next;
	}
	ms->lex->token_list = current;
	return (ms->cmd->num_of_args);
}

t_cmd	*get_cmds(t_minishell *ms)
{
	t_cmd	*new_cmd;
	t_list	*current;
	int i;
	int j;
	int cmd_nr[ms->cmd->num_of_simp_cmds + 1];

	i = 0;
	current = ms->lex->token_list;
	while (current && i < ms->cmd->num_of_simp_cmds + 1)
	{
		new_cmd->simp_cmd = malloc(sizeof(char *) * (ms->cmd->num_of_args + 1));
		if (!new_cmd->simp_cmd)
			return (NULL);
		while (current->type != PIPE)
		{
			if (current->type == WORD)
				ft_stradd_tostrarr(new_cmd->simp_cmd, current->attr);
			//else if (current->type == RE_IN && current->next->type == WORD)
		}
		current = current->next;
		cmd_nr[i] = i;
		i++;
		return (new_cmd);
	}
}
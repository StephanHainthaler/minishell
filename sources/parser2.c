/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:18:02 by juitz             #+#    #+#             */
/*   Updated: 2024/05/17 11:43:04 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**store_input_in_struct(t_minishell *ms)
{
	t_list *current;
	int		i;

	current = ms->lex->token_list;
	i = 0;
	while (current)
	{
		if (current->type >= 1 && current->type <= 7)
		{
			ms->cmd->simp_cmd[i] = ft_strdup(current->attr);
			if (ms->cmd->simp_cmd[i] == NULL)
				return (ft_free(ms->cmd->simp_cmd), NULL);
			i++;
		}
		current = current->next;
	}
	ms->cmd->simp_cmd[i] = NULL;
	return (ms->cmd->simp_cmd);
}

char **parse_tokens_to_struct(t_minishell *ms)
{
	ms->cmd = malloc(sizeof(t_cmd));
	if (ms->cmd == NULL)
		return (NULL);
	ms->cmd->num_of_args = ft_lstsize(ms->lex->token_list);
	ms->cmd->num_of_aval_simp_cmds = 0;
	ms->cmd->simp_cmd = malloc((ms->cmd->num_of_args + 1) * sizeof(char *));
	if (ms->cmd->simp_cmd == NULL)
		return (free(ms->cmd), NULL);
	store_input_in_struct(ms);
	return (ms->cmd->simp_cmd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:26:12 by juitz             #+#    #+#             */
/*   Updated: 2024/05/06 15:05:38 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_simp_cmd *parse_tokens_to_struct(t_lexer *lex)
{
	t_simp_cmd	*simp_cmd;
	t_list		*current;
	int			i;

	simp_cmd = malloc(sizeof(t_simp_cmd));
	if (simp_cmd == NULL)
		return (NULL);
	simp_cmd->num_of_args = ft_lstsize(lex->token_list);
	simp_cmd->num_of_aval_args = 0;
	simp_cmd->args = malloc((simp_cmd->num_of_args + 1) * sizeof(char *));
	if (simp_cmd->args == NULL)
		return (free(simp_cmd), NULL);
	current = lex->token_list;
	i = 0;
	while (current)
	{
		if (current->type == WORD)
		{
			simp_cmd->args[i] = ft_strdup(current->attr);
			if (simp_cmd->args[i] == NULL)
			{
				//free
				return (NULL);
			}
			simp_cmd->num_of_aval_args++;
			i++;
		}
		current = current->next;
	}
	simp_cmd->args[i] = NULL;
	return (simp_cmd);
}




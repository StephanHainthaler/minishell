/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:26:12 by juitz             #+#    #+#             */
/*   Updated: 2024/05/07 16:36:52 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_simp_cmd *parse_tokens_to_struct(t_minishell *ms)
{
	t_simp_cmd	*simp_cmd;
	t_list		*current;
	int			i;
	
	simp_cmd = malloc(sizeof(t_simp_cmd));
	if (simp_cmd == NULL)
		return (NULL);
	ft_putendl_fd("test1", 1);
	simp_cmd->num_of_args = ft_lstsize(ms->lex->token_list);
	ft_putendl_fd("test2", 1);
	simp_cmd->num_of_aval_args = 0;
	simp_cmd->args = malloc((simp_cmd->num_of_args + 1) * sizeof(char *));
	if (simp_cmd->args == NULL)
		return (free(simp_cmd), NULL);
	current = ms->lex->token_list;
	i = 0;
	while (current)
	{
		if (current->type >= 1 && current->type <= 7)
		{
			simp_cmd->args[i] = ft_strdup(current->attr);
			if (simp_cmd->args[i] == NULL)
				return (ft_free(simp_cmd->args), NULL);
			simp_cmd->num_of_aval_args++;
			i++;
		}
		current = current->next;
	}
	simp_cmd->args[i] = NULL;
	return (simp_cmd);
}

int main(void)
{
	t_minishell ms;
	/* t_simp_cmd	simp_cmd;
	t_lexer lex; */
	
	int j = 0;
	//ft_putendl_fd("test1", 1);
	ms.simp_cmd = parse_tokens_to_struct(ms.lex);
	while (ms.simp_cmd->args[j])
	{
		printf("%s", ms.simp_cmd->args[j]);
		j++;
	}
}



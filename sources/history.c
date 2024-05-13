/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:42:21 by juitz             #+#    #+#             */
/*   Updated: 2024/05/13 17:32:37 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* void	add_to_history(t_minishell *ms)
{
	t_list	*new;

	new = ft_lstnew_history(ms->lex->input);
	if (new == NULL)
		return ;
	ft_lstadd_back(&ms->history, new);
}

void	print_history(t_minishell *ms)
{
	t_list	*current;
	int		i;

	current = ms->history;
	i = 1;
	while (current)
	{
		printf("%d %s\n", i, current->input);
		current = current->next;
		i++;
	}
}

void	free_history(t_list **history)
{
	t_list	*current;
	t_list	*tmp;

	current = *history;
	while (current)
	{
		tmp = current->next;
		free(current->input);
		free(current);
		current = tmp;
	}
	*history = NULL;
} */


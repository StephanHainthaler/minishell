/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:34:53 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/13 09:25:13 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_lstdelone(t_list **lst, t_list *node)
{
	t_list	*to_delete;

	if (*lst == NULL)
		return ;
	if (node != NULL)
	{
		to_delete = node;
		if (to_delete->attr != NULL || to_delete->type == WORD)
			free(to_delete->attr);
		node = node->next;
		free(to_delete);
		*lst = node;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:33:31 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/17 09:52:19 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

t_list	*ft_lstnew(t_type type, char *attr)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(1 * sizeof(t_list));
	if (new_lst == NULL)
		return (NULL);
	new_lst->type = type;
	new_lst->attr = attr;
	new_lst->in_squotes = false;
	new_lst->in_dquotes = false;
	new_lst->was_in_quotes = false;
	new_lst->next = NULL;
	return (new_lst);
}

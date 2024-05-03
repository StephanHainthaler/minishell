/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:33:31 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/03 12:05:18 by shaintha         ###   ########.fr       */
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
	new_lst->quote_start = -1;
	new_lst->quote_end = -1;
	new_lst->next = NULL;
	return (new_lst);
}

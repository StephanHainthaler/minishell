/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:34:39 by shaintha          #+#    #+#             */
/*   Updated: 2023/11/13 10:34:40 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_putlst_fd(t_list *lst, int fd)
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		ft_putnbr_fd(temp->content, fd);
		ft_putstr_fd("\t", fd);
		ft_putnbr_fd(temp->index, fd);
		ft_putendl_fd("", fd);
		temp = temp->next;
	}
}

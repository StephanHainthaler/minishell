/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:34:39 by shaintha          #+#    #+#             */
/*   Updated: 2024/04/29 10:14:13 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_putlst_fd(t_list *lst, int fd)
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		ft_putnbr_fd(temp->type, fd);
		ft_putstr_fd("\t", fd);
		ft_putendl_fd(temp->attr, fd);
		temp = temp->next;
	}
}

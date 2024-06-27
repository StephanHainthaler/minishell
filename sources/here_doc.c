/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by juitz             #+#    #+#             */
/*   Updated: 2024/06/27 13:04:10 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int handle_here_doc(int here_doc_fd, char *delimiter)
{
    char    *temp_str;

    while (true)
	{
		temp_str = readline("> ");
		if (temp_str == NULL)
			return (1);
        if (ft_strnstr(temp_str, delimiter, ft_strlen(delimiter)) != NULL \
            && ft_strlen(temp_str) == ft_strlen(delimiter))
			break ;
        ft_putendl_fd(temp_str, here_doc_fd);
        free(temp_str);
	}
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:44:14 by shaintha          #+#    #+#             */
/*   Updated: 2023/09/11 16:55:29 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[])
{   
    if (argc == 2)
    {
        char    *str;

        str = argv[1];
		printf("strlen: %lu\n", strlen(str));
        printf("ft_strlen: %zu\n", ft_strlen(str));
    }
    return (0);
}
*/
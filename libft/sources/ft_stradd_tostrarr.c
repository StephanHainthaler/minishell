/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_tostrarr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:53:43 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/22 15:04:05 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	**ft_stradd_tostrarr(char **strarr, char *str)
{
	char	**new_strarr;
	int		arr_size;
	int		i;

	arr_size = ft_strarrlen(strarr) + 1;
	new_strarr = (char **)malloc((arr_size + 1) * sizeof(char *));
	if (new_strarr == NULL)
		return (NULL);
	ft_putstr_fd("test0\n", 1);
	i = 0;
	if (ft_strarrlen(strarr)== 0)
	{
		new_strarr[0] = ft_strdup(str);
		//NULL CHECK
		return (ft_free(str), new_strarr);
	}
	while (strarr[i])
	{
		ft_putstr_fd(strarr[i], 1);
		new_strarr[i] = ft_strdup(strarr[i]);
		//ft_putstr_fd(new_strarr[i], 1);
		if (new_strarr[i] == NULL)
			return (ft_free_strarr(new_strarr), NULL);
		i++;
	}
	ft_putstr_fd("test2\n", 1);
	new_strarr[i] = ft_strdup(str);
	ft_putstr_fd("test3\n", 1);
	if (new_strarr == NULL)
		return (ft_free_strarr(new_strarr), NULL);
	//ft_putstrarr_fd(new_strarr, 1);
	return (ft_free_strarr(strarr), ft_free(str), new_strarr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_tostrarr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:53:43 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/20 10:56:46 by shaintha         ###   ########.fr       */
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
	i = 0;
	while (i < arr_size - 1)
	{
		new_strarr[i] = ft_strdup(strarr[i]);
		if (new_strarr[i] == NULL)
			return (ft_free_strarr(new_strarr), NULL);
		i++;
	}
	new_strarr[i] = ft_strdup(str);
	if (new_strarr == NULL)
		return (ft_free_strarr(new_strarr), NULL);
	return (ft_free_strarr(strarr), ft_free(str), new_strarr);
}

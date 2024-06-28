/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by juitz             #+#    #+#             */
/*   Updated: 2024/06/28 15:34:44 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int handle_here_doc(int here_doc_fd, char *delim, char **envp, int exit_code)
{
    char    *temp_str;

    while (true)
	{
		temp_str = readline("> ");
		if (temp_str == NULL)
			return (1);
        if (ft_strnstr(temp_str, delim, ft_strlen(delim)) != NULL \
            && ft_strlen(temp_str) == ft_strlen(delim))
			break ;
		if (!(ft_strchr(delim, '\'') || ft_strchr(delim, '"')))
        {
			temp_str = check_for_here_doc_expansion(temp_str, envp, exit_code);
            if (temp_str == NULL)
                return (1);
        }
        ft_putendl_fd(temp_str, here_doc_fd);
		free(temp_str);
	}
    return (0);
}

char	*check_for_here_doc_expansion(char *str, char **envp, int ec)
{
	int		i;

    i = 0;
	while (str[i] != '\0')
	{
			if (str[i] == '$')
			{
				str = expand_here_doc(str, envp, ec, &i);
				if (str == NULL)
					return (NULL);
			}
		i++;
	}
	return (str);
}

char    *expand_here_doc(char *str, char **envp, int exit_code, int *i)
{
    int		len;
	int		pos;
	int		j;

	if (str[*i + 1] == '?')
		return (str = handle_exit_code_expansion(str, exit_code, i));
	if (ft_isspace(str[*i + 1]) == true || str[*i + 1] == '\0'
		|| str[*i + 1] == '$' || str[*i + 1] == '"'
		|| str[*i + 1] == '\'')
		return (str);
	pos = *i;
	len = get_envname_len(str, i);
	j = 0;
	while (envp[j] != NULL)
	{
		if (check_for_env(envp[j], str + pos + 1, len - 1) == true)
			return (*i = pos - 1,
				handle_valid_expansion(str, envp[j], len, pos));
		j++;
	}
	return (*i = pos - 1, handle_invalid_expansion(str, len, pos));
}
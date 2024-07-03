/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by juitz             #+#    #+#             */
/*   Updated: 2024/07/03 13:11:53 by shaintha         ###   ########.fr       */
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

char    *get_temp_name(void)
{
	char	*temp_name;
	char    *temp_str;
	char    *temp_nbr;
	int     i;

	temp_str = ".temp";
	
	temp_nbr = NULL;
	temp_name = NULL;
	i = 0;
	while (i < INT_MAX - 1)
	{
		temp_nbr = ft_itoa(i);
		if (temp_nbr == NULL)
			return (ft_free(temp_nbr), ft_free(temp_name), NULL);
		temp_name = ft_strjoin(temp_str, temp_nbr);
		if (temp_name == NULL)
			return (ft_free(temp_nbr), ft_free(temp_name), NULL);
		printf("%s\n", temp_name);
		if (access(temp_name, F_OK) == -1)
			return (free(temp_nbr), temp_name);
		free(temp_nbr);
		free(temp_name);
		i++;
	}
	return (free(temp_nbr), free(temp_name), NULL);
}

char    *get_random_temp_name(void)
{
	char    *temp_str;
	int		fd_random;

	fd_random = open("/dev/random", O_RDONLY, 0777);
	if (fd_random == -1)
		return (NULL);
	temp_str = (char *)malloc((10 + 1) * sizeof(char));
	if (temp_str == NULL)
		return (close(fd_random), NULL);
	while (true)
	{
		if (read(fd_random, temp_str, 10) == -1)
			return (close(fd_random), free(temp_str), NULL);
		temp_str[10] = '\0';
		//ft_putendl_fd(temp_str, 1);
		if (access(temp_str, F_OK) == -1 && ft_isspace_str(temp_str) == false)
			break ;
	}
	return (close(fd_random), temp_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by juitz             #+#    #+#             */
/*   Updated: 2024/08/05 10:22:51 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Handler for writing to the here_doc.
//Possibly needs to dequote the delimiter for expansion purposes.
//<PARAM> The here_doc fd, the delimiter, 
//<PARAM> the environment pointers & the last exit code.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR; 2 on standard ERROR
int	handle_here_doc(int here_doc_fd, char *delim, char **envp, int exit_code)
{
	char	*temp_str;
	char	*deq_delim;

	deq_delim = dequote(delim);
	if (deq_delim == NULL)
		return (1);
	while (true)
	{
		g_code = 1;
		signal(SIGINT, &sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		temp_str = readline("> ");
		if (temp_str == NULL)
			return (free(deq_delim), \
				ft_putendl_fd("warning: here-doc delimited by EOF", 2), 2);
		if (g_code == 130)
			return (free(deq_delim), 2);
		// if (ft_strnstr(temp_str, delim, ft_strlen(delim)) != NULL && ft_strlen(temp_str) == ft_strlen(delim))
		// 	return (free(deq_delim), ft_putendl_fd("warning: here-doc delimited by EOF", 2), 2);
		if (ft_strnstr(temp_str, deq_delim, ft_strlen(deq_delim)) != NULL \
			&& ft_strlen(temp_str) == ft_strlen(deq_delim))
			break ;
		temp_str = check_here_doc_expansion(temp_str, delim, envp, exit_code);
		if (temp_str == NULL)
			return (free(deq_delim), 1);
		ft_putendl_fd(temp_str, here_doc_fd);
		free(temp_str);
	}
	return (free(deq_delim), 0);
}

//Allocates a random string for a non-existing file in the current directory.
//<PARAM> void
//<RETURN> The temp_name on SUCCESS; NULL on FATAL ERROR
char	*get_random_temp_name(void)
{
	char	*temp_str;
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
		if (access(temp_str, F_OK) == -1 && ft_isspace_str(temp_str) == false)
			break ;
	}
	return (close(fd_random), temp_str);
}

//Checks the input string for possible expansion.
//<PARAM> The input string, the delimiter, 
//<PARAM> the environment pointers & the last exit code.
//<RETURN> The input string on SUCCESS; NULL on FATAL ERROR
char	*check_here_doc_expansion(char *str, char *delim, char **envp, int ec)
{
	int	i;

	if (ft_strchr(delim, '\'') || ft_strchr(delim, '"'))
		return (str);
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

//Expands the input string for the here_doc.
//<PARAM> The input string, the environment pointers, 
//<PARAM> the last exit code & the position in the string.
//<RETURN> The expanded string on SUCCESS; NULL on FATAL ERROR
char	*expand_here_doc(char *str, char **envp, int exit_code, int *i)
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

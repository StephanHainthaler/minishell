/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by juitz             #+#    #+#             */
/*   Updated: 2024/06/27 14:01:32 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int handle_here_doc(int here_doc_fd, char *delim)
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
			//handle_expansion()
        ft_putendl_fd(temp_str, here_doc_fd);
		free(temp_str);
	}
    return (0);
}

char    *expand_here_doc(char *to_expand, char **envp, int exit_code)
{
    int i;

    if (ft_strchr(to_expand, '$') == NULL)
	    return (to_expand);
    i = 0;
    // 		if (to_expand[*i + 1] == '?')
// 		{
// 			to_expand = handle_exit_code_expansion(to_expand, exit_code, i);
// 		}
    
}


// char	*expand_str(char *to_expand, char **envp, int exit_code)
// {
// 	int	len;
// 	int	pos;
// 	int i;
// 	int	j;

// 	if (ft_strchr(to_expand, '$') == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (to_expand[i] != '\0')
// 	{
// 		if (to_expand[i] == '\'' || to_expand[i] == '"')
// 			i++;
// 		if (to_expand[*i + 1] == '?')
// 		{
// 			to_expand = handle_exit_code_expansion(to_expand, exit_code, i);
// 		}
// 	}
// }

// void	handle_quotes_in_expansion_2(char quote, bool in_squotes, bool in_dquotes)
// {	
// 	if (quote == '\'')
// 	{
// 		if (node->in_dquotes == false)
// 			node->in_squotes = !(node->in_squotes);
// 	}
// 	if (quote == '"')
// 	{
// 		if (node->in_squotes == false)
// 			node->in_dquotes = !(node->in_dquotes);
// 	}
// }

// bool	is_str_expandable(char *str)
// {
// 	int		i;
// 	bool	in_sqoutes;
// 	bool	in_dqoutes;

// 	in_sqoutes = false;
// 	in_dqoutes = false;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 		{
// 			if (in_dquotes == false)
// 			in_squotes = !(in_squotes);
// 		}
// 		if (str[i] == '"')
// 		{
// 			if (in_squotes == false)
// 				in_dquotes = !(in_dquotes);
// 		}
// 		if (str[i] == '$' && in_squotes == false)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }
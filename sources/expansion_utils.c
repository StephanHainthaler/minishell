/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/06/24 12:56:20 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_envname_len(t_list *node, int *i)
{
	int	len;

	len = 0;
	while (node->attr[*i] != '\0' && ft_isspace(node->attr[*i]) == false
		&& node->attr[*i] != '\'' && node->attr[*i] != '"')
	{
		if (node->attr[*i + 1] == '$')
		{
			len++;
			break ;
		}
		*i = *i + 1;
		len++;
	}
	return (len);
}

bool	check_for_env(char *str1, char *str2, int len)
{
	if (ft_strncmp(str1, str2, len) != 0)
		return (false);
	if (str1[len] == '=' || str1[len] == '\0')
		return (true);
	return (false);
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

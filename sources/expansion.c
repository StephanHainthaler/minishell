/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:44:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/20 11:41:38 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_for_expansion(t_list **token_list, char **envp)
{
	t_list	*cur_node;
	int		i;

	cur_node = *token_list;
	while (cur_node != NULL)
	{
		if (cur_node->type == WORD)
		{
			i = 0;
			while (cur_node->attr[i] != '\0')
			{
				if (cur_node->attr[i] == '\'' || cur_node->attr[i] == '"')
					handle_quotes_in_expansion(cur_node, cur_node->attr[i]);
				if (cur_node->attr[i] == '$' && cur_node->in_squotes == false)
				{
					cur_node->attr = handle_expansion(cur_node, envp, &i);
					if (cur_node->attr == NULL)
						return (1);
				}
				i++;
			}
		}
		cur_node = cur_node->next;
	}
	return (0);
}

char	*handle_expansion(t_list *node, char **envp, int *i)
{
	int		len;
	int		pos;
	int		j;

	if (ft_isspace(node->attr[*i + 1]) == true || node->attr[*i + 1] == '\0'
		|| node->attr[*i + 1] == '?' || node->attr[*i + 1] == '$'
		|| node->attr[*i + 1] == '"' || node->attr[*i + 1] == '\'')
		return (node->attr);
	pos = *i;
	len = get_envname_len(node, i);
	if (node->attr[*i] == '\'')
	{
		handle_quotes_in_expansion(node, node->attr[*i]);
		if (node->in_squotes == true)
			return (node->attr);
	}
	j = 0;
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], node->attr + pos + 1, len - 1) == 0)
			return (*i = pos - 1,
				handle_valid_expansion(node->attr, envp[j], len, pos));
		j++;
	}
	return (*i = pos - 1, handle_invalid_expansion(node->attr, len, pos));
}

char	*handle_valid_expansion(char *to_expand, char *env, int len, int pos)
{
	char	*exp_str;
	char	*exp_var;
	int		i;
	int		j;

	exp_var = ft_substr(env, len, ft_strlen(env) - len);
	if (exp_var == NULL)
		return (NULL);
	exp_str = (char *)malloc(((ft_strlen(to_expand) \
		- len + ft_strlen(exp_var) + 1) * sizeof(char)));
	if (exp_str == NULL)
		return (free(exp_var), NULL);
	i = 0;
	j = 0;
	while (to_expand[j] != '\0' && j != pos)
		exp_str[i++] = to_expand[j++];
	j = 0;
	while (exp_var[j] != '\0')
		exp_str[i++] = exp_var[j++];
	j = pos + 1 + len - 1;
	while (to_expand[j] != '\0')
		exp_str[i++] = to_expand[j++];
	exp_str[i] = '\0';
	return (free(to_expand), free(exp_var), exp_str);
}

char	*handle_invalid_expansion(char *str, int len, int pos)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i != pos)
		i++;
	ft_strlcpy(new_str, str, i + 1);
	ft_strlcat(new_str + i, str + i + len, ft_strlen(str) - len - i + 1);
	free(str);
	return (new_str);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:44:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/13 16:09:37 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_for_expansion(t_list **token_list, char **envp)
{
	t_list	*current_node;
	char	quote;
	int		i;

	current_node = *token_list;
	while (current_node != NULL)
	{
		if (current_node->type == WORD)
		{
			i = 0;
			quote = '\0';
			while (current_node->attr[i] != '\0')
			{
				if (current_node->attr[i] == '\'' || current_node->attr[i] == '"')
					quote = handle_quotes_in_expansion(current_node, current_node->attr[i]);
				if (current_node->attr[i] == '$' && current_node->in_squotes == false)
				{
					current_node->attr = handle_expansion(current_node, envp, &i, quote);
					if (current_node->attr == NULL)
						return (1);
					continue ;
				}
				i++;
			}
		}
		current_node = current_node->next;
	}
	return (0);
}

char	*handle_expansion(t_list *node, char **envp, int *i, char quote)
{
	int		len;
	int		pos;
	int		j;

	quote = '\0';
	if (ft_isspace(node->attr[*i + 1]) == true || node->attr[*i + 1] == '\0'
		|| node->attr[*i + 1] == '\'' || node->attr[*i + 1] == '"'
		|| node->attr[*i + 1] == '?' || node->attr[*i + 1] == '$')
		return (*i = *i + 1, node->attr);
	pos = *i + 1;
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
	j = 0;
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], node->attr + pos, len - 1) == 0)
			return (*i = 0, handle_valid_expansion(node->attr, \
				envp[j], len, pos));
		j++;
	}
	return (*i = 0, handle_invalid_expansion(node->attr, len));
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
	while (to_expand[j] != '\0' && to_expand[j] != '$')
		exp_str[i++] = to_expand[j++];
	j = 0;
	while (exp_var[j] != '\0')
		exp_str[i++] = exp_var[j++];
	j = pos + len - 1;
	while (to_expand[j] != '\0')
		exp_str[i++] = to_expand[j++];
	exp_str[i] = '\0';
	return (free(to_expand), free(exp_var), exp_str);
}

char	*handle_invalid_expansion(char *str, int len)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	ft_strlcpy(new_str, str, i + 1);
	ft_strlcat(new_str + i, str + i + len, ft_strlen(str) - len - i + 1);
	free(str);
	return (new_str);
}

char	handle_quotes_in_expansion(t_list *node, char quote)
{
	if (quote == '\'')
	{
		if (node->in_squotes == false && node->in_dquotes == false)
			node->in_squotes = true;
		else
			node->in_squotes = false;
	}
	else
	{
		if (node->in_dquotes == false && node->in_squotes == false)
			node->in_dquotes = true;
		else
			node->in_dquotes = false;
	}
	if (node->in_dquotes == false && node->in_squotes == false)
		quote = '\0';
	return (quote);
}

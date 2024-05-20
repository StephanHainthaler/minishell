/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:46:31 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/20 09:35:51 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_quotes(t_lexer *lex, char quote, int *len)
{
	bool	is_closed;

	is_closed = false;
	lex->i++;
	*len += 1;
	while (lex->input[lex->i] != '\0')
	{
		if (lex->input[lex->i] == quote)
		{
			is_closed = true;
			break ;
		}
		lex->i++;
		*len += 1;
	}
	if (is_closed == false)
		return (1);
	return (0);
}

int	check_for_dequotation(t_list **token_list)
{
	t_list	*current_node;

	current_node = *token_list;
	while (current_node != NULL)
	{
		if (current_node->type == 1)
		{
			if (ft_strchr(current_node->attr, '"') != NULL
				|| ft_strchr(current_node->attr, '\'') != NULL)
			{
				current_node->attr = handle_dequotation(\
					current_node->attr, 0, 0);
				if (current_node->attr == NULL)
					return (1);
			}
		}
		current_node = current_node->next;
	}
	return (0);
}

char	*handle_dequotation(char *to_trim, int i, int j)
{
	char	*trim_str;
	char	quote;

	trim_str = (char *)malloc(
			(get_dequoted_strlen(to_trim) + 1) * (sizeof(char)));
	if (trim_str == NULL)
		return (NULL);
	while (to_trim[i] != '\0')
	{
		if (to_trim[i] == '\'' || to_trim[i] == '"')
		{
			quote = to_trim[i++];
			while (to_trim[i] != quote)
				trim_str[j++] = to_trim[i++];
			i++;
		}
		else
			trim_str[j++] = to_trim[i++];
	}
	trim_str[j] = '\0';
	return (free(to_trim), trim_str);
}

int	get_dequoted_strlen(char *str)
{
	char	quote;
	int		num_of_quotes;
	int		i;

	num_of_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			num_of_quotes++;
			quote = str[i++];
			while (str[i] != '\0')
			{
				if (str[i] == quote)
				{
					num_of_quotes++;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (ft_strlen(str) - num_of_quotes);
}

void	handle_quotes_in_expansion(t_list *node, char quote)
{
	if (quote == '\'')
	{
		if (node->in_dquotes == false)
			node->in_squotes = !(node->in_squotes);
	}
	if (quote == '"')
	{
		if (node->in_squotes == false)
			node->in_dquotes = !(node->in_dquotes);
	}
}

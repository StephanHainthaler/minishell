/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:46:31 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/25 14:56:29 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*dequote(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	new_str = (char *)malloc((get_dequoted_strlen(str) + 1) * (sizeof(char)));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] != quote)
				new_str[j++] = str[i++];
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	handle_quote_closure(t_lexer *lex, char quote, int *len)
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

void	handle_quotes_in_expansion2(char quote, bool *in_sq, bool *in_dq)
{
	if (quote == '\'')
	{
		if (*in_dq == false)
			*in_sq = !(*in_sq);
	}
	if (quote == '"')
	{
		if (*in_sq == false)
			*in_dq = !(*in_dq);
	}
}

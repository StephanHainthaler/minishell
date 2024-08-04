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

//Takes a string and duplicates it in dequoted from.
//The dequoted string needs to be freed.
//<PARAM> The to be dequoted string.
//<RETURN> The string on SUCCESS; NULL on FATAL ERROR
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

//Takes a string and counts its length in dequoted from.
//<PARAM> The to be dequoted string.
//<RETURN> The lenght of the dequoted string on SUCCESS
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

//During tokenizing, keeps check, if there no open quotes.
//<PARAM> The lexer struct, the opened quote, the current position in the string.
//<RETURN> 0 on SUCCESS; 1 on standard ERROR
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

//During expansion process, keeps check of current state of quotes.
//<PARAM> The current node, the quote to be verified.
//<RETURN> void
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

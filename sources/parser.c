/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:26:12 by juitz             #+#    #+#             */
/*   Updated: 2024/05/03 15:02:35 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int check_valid_input(t_lexer *lex)
{
	t_list *head;
	t_list *current;

	head = lex->token_list;
	current = lex->token_list;
	while (current != NULL)
	{
		if (current->type == RE_IN && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `<'"), 1);
		if (current->type == RE_OUT && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `>'"), 1);
		if (current->type == HERE_DOC && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `<<'"), 1);
		if (current->type == APPEND && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `>>'"), 1);
		current = current->next;
	}
	lex->token_list = head;
	return (0);
}
	
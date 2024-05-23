/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:41:06 by juitz             #+#    #+#             */
/*   Updated: 2024/05/23 15:01:20 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool is_valid_input(t_lexer *lex)
{
	t_list *head;
	t_list *current;
	bool	has_wrd;

	head = lex->token_list;
	current = lex->token_list;
	has_wrd = false;
	while (current != NULL)
	{
		if (current->type == WORD)
			has_wrd = true;
		if (current->type == PIPE)
			has_wrd = false;
		if (current->type == PIPE && has_wrd == false)
			return (ft_error("command has no word"), false);
		if (current->type == RE_IN && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `<'"), false);
		if (current->type == RE_OUT && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `>'"), false);
		if (current->type == HERE_DOC && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `<<'"), false);
		if (current->type == APPEND && current->next != NULL && current->next->type != WORD)
			return (ft_error("parse error near `>>'"), false);
		if (current->type != WORD && current->next == NULL)
			return (ft_error("word token required as last input"), false);
		current = current->next;
	}
	if (has_wrd == false)
		return (ft_error("command has no word"), false);
	lex->token_list = head;
	return (true);
}
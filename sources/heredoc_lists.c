/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:12:06 by juitz             #+#    #+#             */
/*   Updated: 2024/06/10 13:59:54 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/history.h>

void	heredoc(t_lexer *lex)
{
	char *delim;
	t_list	*current;
	t_list	*hd_input;

	current = lex->token_list;
	if (current->type == HERE_DOC)
	{
		current = current->next;
		delim = current->attr;
		while (1)
		{
			hd_input->tmp = readline("heredoc>");
			if (delim[0] == '\'' || delim[0] == '\"')
				handle_expansion(hd_input, lex->envp, &lex->i);
			ft_lstadd_back(&lex->here_doc, hd_input);
			add_history(hd_input->tmp);
			
			if (ft_strncmp(hd_input->tmp, delim, ft_strlen(delim) == 0))
				return(free(lex->here_doc->tmp), free(delim))
		}
	}
}
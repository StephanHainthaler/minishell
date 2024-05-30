/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:02:54 by juitz             #+#    #+#             */
/*   Updated: 2024/05/30 18:09:18 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/history.h>

char	**parse_heredoc(t_minishell *ms)
{
	char *line;
	char **full_input;
	char *delim;
	t_list	*current;

	current = ms->lex->token_list;
	if (current->type == HERE_DOC)
	{
		current = current->next;
		delim = current->attr;
	}
	while (1)
	{
		line = readline("heredoc>");
		full_input = ft_split(line, '\n');
		if (ft_strncmp(ms->lex->input, delim, ft_strlen(delim)) == 0)
			return(free(line), free(delim), full_input);
	}
	return (NULL);
}
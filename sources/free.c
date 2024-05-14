/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:00:58 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/14 12:31:03 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_minishell(t_minishell *ms)
{
	if (ms->envp != NULL)
		ft_free_strarr(ms->envp);
}

void	free_lexer(t_lexer *lex)
{
	if (lex->token_list != NULL)
		ft_lstclear(&lex->token_list);
	free(lex);
}

void	free_and_exit(t_minishell *ms)
{
	free_lexer(ms->lex);
	free_minishell(ms);
	rl_clear_history();
	exit(0);
}

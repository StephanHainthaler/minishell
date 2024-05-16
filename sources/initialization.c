/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:52:39 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/14 14:36:41 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[])
{
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = ft_strarrdup(env);
	if (ms->envp == NULL)
		return (1);
	return (0);
}

int	initialize_lexer(t_minishell *ms)
{
	ms->lex = (t_lexer *)malloc(sizeof(t_lexer));
	if (ms->lex == NULL)
		return (1);
	ms->lex->token_list = NULL;
	ms->lex->input = NULL;
	ms->lex->i = 0;
	ms->lex->envp = ms->envp;
	return (0);
}

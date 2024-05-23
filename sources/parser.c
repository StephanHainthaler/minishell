/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/23 14:41:46 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <stdbool.h>

int	count_pipes(t_minishell *ms)
{
	t_list *current;

	current = ms->lex->token_list;
	while (current != NULL)
	{
		if (ms->lex->token_list->type == PIPE)
			ms->num_of_cmds++;
		current = current->next;
	}
	ms->lex->token_list = current;
	return (ms->num_of_cmds + 1);
}
// int	num_of_args(t_minishell *ms)
// {
// 	t_list *current;

// 	current = ms->lex->token_list;
// 	while (current != NULL)
// 	{
// 		if (current->type == WORD)
// 			ms->cmds->num_of_args++;
// 		current = current->next;
// 	}
// 	ms->lex->token_list = current;
// 	return (ms->cmds->num_of_args);
// }

int	get_cmds(t_minishell *ms)
{
	//t_cmd	**cmds;
	//t_cmd	*new_cmd;
	t_list	*current;
	//int cmd_nr[ms->cmds->num_of_simp_cmds + 1];
	int i;
	bool	has_wrd;

	//ms->num_of_cmds = count_pipes(ms) - 1;
	printf("%d\n", ms->num_of_cmds);
	ms->cmds = (t_cmd **)malloc(ms->num_of_cmds * sizeof(t_cmd *));
	if (ms->cmds == NULL)
		return (1);
	i = 0;
	current = ms->lex->token_list;
	while (current && current->next) //&& i < ms->cmds->num_of_simp_cmds + 1)
	{
		ms->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
		initialize_cmd(ms->cmds[i], i);
		printf("test\n");
		//NULL CHECK
		// cmds->simp_cmd = malloc(sizeof(char *) * (ms->cmds->num_of_args + 1));
		// if (!cmds->simp_cmd)
		// 	return (NULL);
		has_wrd = false;
		while (current->next != NULL && current->type != PIPE)
		{
			printf("test3\n");
			if (current->type == WORD)
			{
				printf("test4\n");
				has_wrd = true;
				ms->cmds[i]->simp_cmd = ft_stradd_tostrarr(ms->cmds[i]->simp_cmd, current->attr);
				if (!ms->cmds)
					return (1); //free)
				ft_putstrarr_fd(ms->cmds[i]->simp_cmd, 1);
			}
			// else if (current->type == RE_IN)
			// 	ms->cmd->infile = current->next->attr;
			// else if (current->type == RE_OUT)
			// 	ms->cmd->outfile = current->next->attr;
			printf("test5\n");
			//NULL CHECK
			current = current->next;
		}
		current = current->next;
		i++;
		printf("test6\n");
	}
	if (has_wrd == false)
		return (ft_error("parse error: need at least one word"), 1);
	return (0);
}
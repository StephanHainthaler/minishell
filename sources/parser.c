/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/27 13:53:35 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <curses.h>
#include <stdbool.h>

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	if (initialize_executor(ms) == 1)
		return (1);
	if (get_cmds(ms->exec, &ms->lex->token_list) == 1)
		return (free_executor(ms->exec), 1);
	printf("Print all cmds:\n");
	i = 0;
	while (i < ms->exec->num_of_cmds)
		ft_print_cmd(ms->exec->cmds[i++]);
	printf("\n");
	return (0);
}

// int	parse_input(t_minishell *ms)
// {
// 	if (initialize_executor(ms) == 1)
// 		return (1);
// 	// if (get_cmds(ms->exec, &ms->lex->token_list) == 1)
// 	// 	return (free_executor(ms->exec), 1);
// 	return (0);
// }


int		get_cmds(t_executor *exec, t_list **list)
{
	t_list	*current;
	int i;
	int	j;

	i = 0;
	j = 0;
	current = *list;
	while (current) //&& i < ms->cmds->num_of_simp_cmds + 1)
	{
		if (current->type == WORD)
		{
			exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, current->attr);
			if (exec->cmds[i]->simp_cmd == NULL)
				return (1); //free)
			printf("Added %s to simp_cmd\n", exec->cmds[i]->simp_cmd[j]);
			j++;
		}
		if (current->type == RE_IN || current->type == APPEND)
		{
			current = current->next;
			exec->cmds[i]->infile = current->attr;
			exec->cmds[i]->in_fd = get_fd(exec->cmds[i]->infile, true);
		}
		if (current->type == RE_OUT)
		{
			current = current->next;
			exec->cmds[i]->outfile = current->attr;
			exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false);
		}
		if (current->type == PIPE)
		{
			printf("End of cmd\n");
			//current = current->next;
			//ft_print_cmd(exec->cmds[i]);
			//current = current->next;
			exec->cmds[i]->cmd_nbr = i;
			j = 0;
			i++;
		}
			//else if (current->type == HERE_DOC)
			//NULL CHECK
		printf("Next node\n");
		current = current->next;
	}
	printf("End of cmd\n");
	return (0);
}

int	count_cmds(t_list **list)
{
	t_list	*current_node;
	int		num_of_cmds;

	current_node = *list;
	num_of_cmds = 1;
	while (current_node != NULL)
	{
		if (current_node->type == PIPE)
			num_of_cmds++;
		current_node = current_node->next;
	}
	return (num_of_cmds);
}

void	ft_print_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (i < ft_strarrlen(cmd->simp_cmd))
	{
		printf("cmd->simp_cmd[%zu]: %s\n", i, cmd->simp_cmd[i]);
		i++;
	}
	printf("cmd->infile: %s\n", cmd->infile);
	printf("cmd->outfile: %s\n", cmd->outfile);
	printf("cmd->in_fd: %d\n", cmd->in_fd);
	printf("cmd->out_fd: %d\n", cmd->out_fd);
	printf("cmd->cmd_nbr: %d\n", cmd->cmd_nbr);
	//printf("cmd->cmd_path: %s\n", cmd->cmd_path);
}

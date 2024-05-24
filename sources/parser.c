/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/24 16:56:24 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <curses.h>
#include <stdbool.h>

void	ft_print_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->simp_cmd[i])
	{
		printf("cmd->simp_cmd[%d]: %s\n", i, cmd->simp_cmd[i]);
		i++;
	}
	//printf("cmd->cmd_path: %s\n", cmd->cmd_path);
	printf("cmd->infile: %s\n", cmd->infile);
	printf("cmd->outfile: %s\n", cmd->outfile);
	printf("cmd->in_fd: %d\n", cmd->in_fd);
	printf("cmd->out_fd: %d\n", cmd->out_fd);
	printf("cmd->cmd_nbr: %d\n", cmd->cmd_nbr);
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
int		get_cmds(t_executor *exec, t_list **list)
{
	t_list	*current;
	t_cmd	cmd;
	int i;

	i = 0;
	current = *list;
	while (current) //&& i < ms->cmds->num_of_simp_cmds + 1)
	{
		// cmds->simp_cmd = malloc(sizeof(char *) * (ms->cmds->num_of_args + 1));
		// if (!cmds->simp_cmd)
		// 	return (NULL);
		while (current->next != NULL && current->type != PIPE)
		{
			if (current->type == WORD)
			{
				exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, current->attr);
				if (!exec->cmds[i]->simp_cmd)
					return (1); //free)
				ft_putstrarr_fd(exec->cmds[i]->simp_cmd, 1);
			}
			else if (current->type == RE_IN || current->type == APPEND)
			{
				cmd.infile = current->next->attr;
				get_fd(cmd.infile, true);
			}
			else if (current->type == RE_OUT)
			{
				cmd.outfile = current->next->attr;
				get_fd(cmd.outfile, false);
			}
			//else if (current->type == HERE_DOC)
			//NULL CHECK
			current = current->next;
		}
		current = current->next;
		ft_print_cmd(exec->cmds[i]);
		cmd.cmd_nbr = i;
		i++;
	}
	return (0);
}

int	parse_input(t_minishell *ms)
{
	if (initialize_executor(ms) == 1)
		return (1);
	// if (get_cmds(ms->exec, &ms->lex->token_list) == 1)
	// 	return (free_executor(ms->exec), 1);
	return (0);
}
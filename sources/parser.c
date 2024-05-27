/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:56 by juitz             #+#    #+#             */
/*   Updated: 2024/05/27 13:48:29 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	parse_input(t_minishell *ms)
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

int		get_cmds(t_executor *exec, t_list **list)
{
	t_list	*current;
	int i;

	i = 0;
	current = *list;
	while (current)
	{
		if (current->type == WORD)
		{
			exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, current->attr);
			if (exec->cmds[i]->simp_cmd == NULL)
				return (1);
		}
		if (current->type == RE_IN)
		{
			current = current->next;
			if (exec->cmds[i]->infile != NULL)
				free(exec->cmds[i]->infile);
			exec->cmds[i]->infile = ft_strdup(current->attr);
			exec->cmds[i]->in_fd = get_fd(exec->cmds[i]->infile, true);
		}
		if (current->type == RE_OUT)
		{
			current = current->next;
			if (exec->cmds[i]->outfile != NULL)
				free(exec->cmds[i]->outfile);
			exec->cmds[i]->outfile = ft_strdup(current->attr);
			exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false);
		}
		if (current->type == PIPE)
		{
			exec->cmds[i]->cmd_nbr = i;
			i++;
		}
		//of (APPEND)
		//if (current->type == HERE_DOC)
			//NULL CHECK
		current = current->next;
	}
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

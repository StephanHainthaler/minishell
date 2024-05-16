/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:26:12 by juitz             #+#    #+#             */
/*   Updated: 2024/05/16 12:17:40 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**store_input_in_struct(t_minishell *ms)
{
	t_list *current;
	int		i;

	current = ms->lex->token_list;
	i = 0;
	while (current)
	{
		if (current->type >= 1 && current->type <= 7)
		{
			ms->cmd->simp_cmd[i] = ft_strdup(current->attr);
			if (ms->cmd->simp_cmd[i] == NULL)
				return (ft_free(ms->cmd->simp_cmd), NULL);
			ms->cmd->num_of_simp_cmds++;
			i++;
		}
		current = current->next;
	}
	ms->cmd->simp_cmd[i] = NULL;
	return (ms->cmd->simp_cmd);
}

char **parse_tokens_to_struct(t_minishell *ms)
{
	ms->cmd = malloc(sizeof(t_cmd));
	if (ms->cmd == NULL)
		return (NULL);
	ms->cmd->num_of_args = ft_lstsize(ms->lex->token_list);
	ms->cmd->num_of_aval_simp_cmds = 0;
	ms->cmd->simp_cmd = malloc((ms->cmd->num_of_args + 1) * sizeof(char *));
	if (ms->cmd->simp_cmd == NULL)
		return (free(ms->cmd), NULL);
	store_input_in_struct(ms);
	ms->cmd->simp_cmd = ft_split(ms->lex->input, '|');
	return (ms->cmd->simp_cmd);
}
char **split_command(t_minishell *ms)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ms->cmd->full_cmd = malloc((ms->cmd->num_of_simp_cmds + 1) * sizeof(char *));
	if (ms->cmd->full_cmd == NULL)
		return (NULL);
	while (ms->cmd->simp_cmd[i])
	{
		if (ms->cmd->simp_cmd[i][0] == '|')
		{
			i++;
			j++;
		}
		ms->cmd->full_cmd[j] = ft_strjoin(ms->cmd->full_cmd[j], ms->cmd->simp_cmd[i]);
		if (ms->cmd->full_cmd[j] == NULL)
			return (ft_free(ms->cmd->full_cmd), NULL);
		i++;
	}
	ms->cmd->full_cmd[j + 1] = NULL;
	return (ms->cmd->full_cmd);
}
/* int main(void)
{
	t_minishell ms;
	t_simp_cmd	simp_cmd;
	t_lexer lex;
	
	int j = 0;
	//ft_putendl_fd("test1", 1);
	ms.simp_cmd = parse_tokens_to_struct(ms.lex);
	while (ms.simp_cmd->args[j])
	{
		printf("%s", ms.simp_cmd->args[j]);
		j++;
	}
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:26:12 by juitz             #+#    #+#             */
/*   Updated: 2024/05/13 17:58:00 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* t_simp_cmd *parse_tokens_to_struct(t_minishell *ms)
{
	t_list	*current;
	int		i;

	ms->simp_cmd = malloc(sizeof(t_simp_cmd));
	if (ms->simp_cmd == NULL)
		return (NULL);
	ms->simp_cmd->num_of_args = ft_lstsize(ms->lex->token_list);
	ms->simp_cmd->num_of_aval_args = 0;
	ms->simp_cmd->args = malloc((ms->simp_cmd->num_of_args + 1) * sizeof(char *));
	if (ms->simp_cmd->args == NULL)
		return (free(ms->simp_cmd), NULL);
	current = ms->lex->token_list;
	i = 0;
	while (current)
	{
		if (current->type >= 1 && current->type <= 7)
		{
			ms->simp_cmd->args[i] = ft_strdup(current->attr);
			if (ms->simp_cmd->args[i] == NULL)
				return (ft_free(ms->simp_cmd->args), NULL);
			ms->simp_cmd->num_of_aval_args++;
			i++;
		}
		current = current->next;
	}
	//store_input_in_struct(ms);
	ms->simp_cmd->args[i] = NULL;
	return (ms->simp_cmd);
} */

t_simp_cmd	*store_input_in_struct(t_minishell *ms)
{
	t_list *current;
	int		i;

	printf("test0\n");
	current = ms->lex->token_list;
	i = 0;
	printf("test1\n");
	while (current)
	{
		if (current->type >= 1 && current->type <= 7)
		{
			ms->simp_cmd->args[i] = ft_strdup(current->attr);
			if (ms->simp_cmd->args[i] == NULL)
				return (ft_free(ms->simp_cmd->args), NULL);
			ms->simp_cmd->num_of_aval_args++;
			i++;
		}
		current = current->next;
	}
	printf("test2\n");
	ms->simp_cmd->args[i] = NULL;
	return (ms->simp_cmd);
}

t_simp_cmd *parse_tokens_to_struct(t_minishell *ms)
{
	ms->simp_cmd = malloc(sizeof(t_simp_cmd));
	printf("test\n");
	if (ms->simp_cmd == NULL)
		return (NULL);
	printf("test1\n");
	//ms->simp_cmd->num_of_args = ft_lstsize(ms->lex->token_list);
	printf("test2\n");
	ms->simp_cmd->num_of_aval_args = 0;
	ms->simp_cmd->args = malloc((ms->simp_cmd->num_of_args + 1) * sizeof(char *));
	printf("test3\n");
	if (ms->simp_cmd->args == NULL)
		return (free(ms->simp_cmd), NULL);
	printf("test4\n");
	store_input_in_struct(ms);
	printf("test8\n");
	return (ms->simp_cmd);
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



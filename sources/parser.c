#include "../headers/minishell.h"

int	count_pipes(t_minishell *ms)
{
	t_list *head;
	t_list *current;

	head = ms->lex->token_list;
	current = ms->lex->token_list;
	while (current != NULL)
	{
		if (ms->lex->token_list->type == PIPE)
			ms->cmd->num_of_simp_cmds++;
		current = current->next;
	}
	ms->lex->token_list = head;
	return (ms->cmd->num_of_simp_cmds);
}

char ***split_commands(t_minishell *ms)
{
	int i;

	i = 0;
	ms->cmd->simp_cmd = ft_split(ms->lex->input, '|');
	if(!ms->cmd->simp_cmd)
		return (NULL);
	ms->cmd->cmd_list = malloc(sizeof(char **) * (ms->cmd->num_of_simp_cmds + 1));
	while (i <= ms->cmd->num_of_simp_cmds)
	{
		ms->cmd->cmd_list[i] = ft_split(ms->cmd->simp_cmd[i], ' ');
		if(!ms->cmd->cmd_list)
			return (NULL);
		i++;
	}
	ms->cmd->cmd_list[i] = NULL;
	return (ms->cmd->cmd_list);
}
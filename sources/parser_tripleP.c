#include "../headers/minishell.h"

int	count_pipes(t_minishell *ms)
{
	t_list *current;

	current = ms->lex->token_list;
	while (current != NULL)
	{
		if (ms->lex->token_list->type == PIPE)
			ms->cmd->num_of_simp_cmds++;
		current = current->next;
	}
	ms->lex->token_list = current;
	return (ms->cmd->num_of_simp_cmds + 1);
}

char ***split_commands(t_minishell *ms)
{
	t_list *current;
	int i;
	int j;

	i = 0;
	current = ms->lex->token_list;
	while (current)
	{
		while (current->type != PIPE)
		{
			if (current->type == WORD)
			{
				ft_stradd_tostrarr(ms->cmd->simp_cmd, current->attr);
			if (current->type == RE_IN)
				//change fd
			current = current->next;
		}
		if (current->type == PIPE)
		{
			ms->cmd->
		}

	ms->lex->token_list = current;
	ms->cmd->cmd_arr = malloc(sizeof(char **) * (ms->cmd->num_of_simp_cmds + 1));
	while (i <= ms->cmd->num_of_simp_cmds)
	{
		ms->cmd->cmd_arr[i] = ft_split(ms->cmd->simp_cmd[i], '|');
		if(!ms->cmd->cmd_arr)
			return (NULL);
		i++;
	}
	ms->cmd->cmd_arr[i] = NULL;
	return (ms->cmd->cmd_arr);
}

	// ms->cmd->simp_cmd = ft_split(ms->lex->input, '|');
	// if(!ms->cmd->simp_cmd)
	// 	return (NULL);
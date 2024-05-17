#include "../headers/minishell.h"

int count_pipes(t_minishell *ms)
{
	int i;

	i = 0;
	while (ms->lex->input[i])
	{
		if (ms->lex->input[i] == '|')
			ms->cmd->num_of_simp_cmds++;
		i++;
	}
	return (ms->cmd->num_of_simp_cmds);
}

char ***split_commands(t_minishell *ms)
{
	int i;

	i = 0;
	ms->cmd->simp_cmd = ft_split(ms->lex->input, '|');
	ms->cmd->cmd_list = malloc(sizeof(char **) * (ms->cmd->num_of_simp_cmds + 1));
	while (i < ms->cmd->num_of_simp_cmds)
	{
		ms->cmd->cmd_list[i] = ft_split(ms->cmd->simp_cmd[i], ' ');
		i++;
	}
	ms->cmd->cmd_list[i] = NULL;
	return ms->cmd->cmd_list;
}
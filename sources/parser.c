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
	printf("%s", ms->lex->input);
	
	ms->cmd->simp_cmd = ft_split(ms->lex->input, '|');
	if(!ms->cmd->simp_cmd)
		return (NULL);
	printf("Test2\n");
	ms->cmd->cmd_list = malloc(sizeof(char **) * (ms->cmd->num_of_simp_cmds + 1));
	printf("Test3\n");
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
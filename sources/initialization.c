/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:52:39 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/05 10:18:35 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Initializes the main struct of the program.
//<PARAM> The to be initialzed main struct, 
//<PARAM> the number of main args, the main args & environment pointers.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[])
{
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = ft_strarrdup(env);
	if (ms->envp == NULL)
		return (1);
	// if (env != NULL && is_env_set(env, "SHLVL=") == true)
	// {
	// 	ms->envp = increase_shlvl(ms->envp);
	// 	if (ms->envp == NULL)
	// 		return (1);
	// }
	ms->lex = NULL;
	ms->exec = NULL;
	ms->last_exit_code = 0;
	return (0);
}

//Initializes the lexer struct.
//<PARAM> The main struct of the program.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	initialize_lexer(t_minishell *ms)
{
	ms->lex = (t_lexer *)malloc(sizeof(t_lexer));
	if (ms->lex == NULL)
		return (1);
	ms->lex->token_list = NULL;
	ms->lex->input = NULL;
	ms->lex->i = 0;
	ms->lex->envp = ms->envp;
	return (0);
}

//Initializes the first part of the executor struct.
//<PARAM> The main struct of the program.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	initialize_executor(t_minishell *ms)
{
	int	i;

	ms->exec = (t_executor *)malloc(sizeof(t_executor));
	if (ms->exec == NULL)
		return (1);
	ms->exec->num_of_cmds = count_cmds(&ms->lex->token_list);
	ms->exec->num_of_pipes = ms->exec->num_of_cmds - 1;
	ms->exec->cmds = (t_cmd **)malloc(ms->exec->num_of_cmds * sizeof(t_cmd *));
	if (ms->exec->cmds == NULL)
		return (free(ms->exec), 1);
	i = 0;
	while (i < ms->exec->num_of_cmds)
	{
		ms->exec->cmds[i] = initialize_cmd(ms->exec->cmds[i], i);
		if (ms->exec->cmds[i] == NULL)
			return (free_cmds(ms->exec->cmds, i), free(ms->exec), 1);
		i++;
	}
	ms->exec->is_path_set = is_env_set(ms->envp, "PATH=");
	ms->exec->paths = NULL;
	ms->exec->exit_status = ms->last_exit_code;
	ms->exec->envp = ms->envp;
	return (0);
}

//Initializes the second part of the executor struct.
//<PARAM> The main struct of the program.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	initialize_executor_2(t_minishell *ms)
{
	int	error_flag;

	error_flag = 0;
	if (ms->exec->is_path_set == true)
	{
		ms->exec->paths = get_paths(ms->exec, &error_flag);
		if (ms->exec->paths == NULL && error_flag == 1)
			return (1);
	}
	return (0);
}

//Initializes a cmd struct.
//<PARAM> The to be initialzed cmd struct & the number of the cmd.
//<RETURN> The cmd on SUCCESS; NULL on FATAL ERROR
t_cmd	*initialize_cmd(t_cmd *cmd, int cmd_nbr)
{
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->simp_cmd = NULL;
	cmd->cmd_path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->here_doc = NULL;
	if (cmd->here_doc == NULL)
	{
		cmd->here_doc = get_random_temp_name();
		if (cmd->here_doc == NULL)
			return (free(cmd), NULL);
	}
	cmd->in_fd = 0;
	cmd->out_fd = 1;
	cmd->cmd_nbr = cmd_nbr;
	cmd->has_here_doc = false;
	cmd->is_parent = true;
	return (cmd);
}

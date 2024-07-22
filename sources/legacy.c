/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/22 14:25:19 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	free_pipes(int **pipes, int num_of_pipes)
// {
// 	int	i;

// 	if (pipes == NULL)
// 		return ;
// 	i = 0;
// 	while (i < num_of_pipes)
// 	{
// 		if (pipes[i][0] != -1)
// 			close(pipes[i][0]);
// 		if (pipes[i][1] != -1)
// 			close(pipes[i][1]);
// 		ft_free(pipes[i]);
// 		pipes[i] = NULL;
// 		i++;	
// 	}
// 	free(pipes);
// 	pipes = NULL;
// }

// int	initialize_executor_2(t_minishell *ms, int i)
// {
// 	int	error_flag;

// 	error_flag = 0;
// 	i = 0;
// 	// ms->exec->cpids = (pid_t *)malloc(ms->exec->num_of_cmds * sizeof(pid_t));
// 	// if (ms->exec->cpids == NULL)
// 	// 	return (1);
// 	// ms->exec->pipes = (int **)malloc(ms->exec->num_of_pipes * sizeof(int *));
// 	// if (ms->exec->pipes == NULL)
// 	// 	return (free(ms->exec->cpids), 1);
// 	// while (i < ms->exec->num_of_pipes)
// 	// {
// 	// 	ms->exec->pipes[i] = (int *)malloc(2 * sizeof(int));
// 	// 	if (ms->exec->pipes[i] == NULL)
// 	// 		return (free_pipes(ms->exec->pipes, i), 1);
// 	// 	ms->exec->pipes[i][0] = -1;
// 	// 	ms->exec->pipes[i][1] = -1;
// 	// 	i++;
// 	// }
// 	if (is_path_set(ms->envp) == true)
// 	{
// 		ms->exec->paths = get_paths(ms->exec, &error_flag);
// 		if (ms->exec->paths == NULL && error_flag == 1)
// 			return (1);
// 	}
// 	return (0);
// }

// int	read_input(t_minishell *ms)
// {
// 	int	error_check;

// 	error_check = 0;
// 	if (initialize_lexer(ms) == 1)
// 		return (1);
// 	while (true)
// 	{
// 		ms->lex->input = readline("./minishell$ ");
// 		if (ms->lex->input == NULL)
// 			return (1);
// 		if (ft_isspace_str(ms->lex->input) == false)
// 			break ;
// 	}
// 	add_history(ms->lex->input);
// 	error_check = tokenize_input(ms->lex);
// 	if (error_check == 1)
// 		return (1);
// 	if (error_check == 2)
// 		return (free_lexer(ms->lex), 2);
// 	if (check_for_expansion(&ms->lex->token_list, ms->envp, ms->last_exit_code) == 1)
// 		return (1);
// 	if (check_for_dequotation(&ms->lex->token_list) == 1)
// 		return (1);
// 	return (0);
// }

// int handle_here_doc(int here_doc_fd, char *delim, char **envp, int exit_code)
// {
// 	char    *temp_str;

// 	while (true)
// 	{
// 		temp_str = readline("> ");
// 		if (temp_str == NULL)
// 			return (1);
// 		if (ft_strnstr(temp_str, delim, ft_strlen(delim)) != NULL \
// 			&& ft_strlen(temp_str) == ft_strlen(delim))
// 			break ;
// 		if (!(ft_strchr(delim, '\'') || ft_strchr(delim, '"')))
// 		{
// 			temp_str = check_for_here_doc_expansion(temp_str, envp, exit_code);
// 			if (temp_str == NULL)
// 				return (1);
// 		}
// 		ft_putendl_fd(temp_str, here_doc_fd);
// 		free(temp_str);
// 	}
// 	return (0);
// }

// int	get_here_doc(t_executor *exec, char *delim, int i)
// {
// 	if (exec->cmds[i]->infile != NULL)
// 		free(exec->cmds[i]->infile);
// 	if (exec->cmds[i]->in_fd != -1 && exec->cmds[i]->in_fd != 0)
// 		close(exec->cmds[i]->in_fd);
// 	if (exec->cmds[i]->has_here_doc == true)
// 		unlink(exec->cmds[i]->here_doc);
// 	// if (exec->cmds[i]->here_doc == NULL) //access(exec->cmds[i]->here_doc, F_OK) == -1)
// 	// {
// 	// 	exec->cmds[i]->here_doc = get_temp_name();
// 	// 	if (exec->cmds[i]->here_doc == NULL)
// 	// 		return (1);
// 	// 	printf("%s\n", exec->cmds[i]->here_doc);
// 	// }
// 	exec->cmds[i]->has_here_doc = true;
// 	exec->cmds[i]->infile = ft_strdup(exec->cmds[i]->here_doc);
// 	if (exec->cmds[i]->infile == NULL)
// 		return (1); 
// 	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_WRONLY | O_APPEND | O_CREAT, 0777);
//     if (exec->cmds[i]->in_fd == -1)
// 		return (1);
// 	if (handle_here_doc(exec->cmds[i]->in_fd, delim, exec->envp, exec->exit_status) == -1)
// 		return (1);
// 	close(exec->cmds[i]->in_fd);
// 	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_RDONLY, 0777);
// 	if (exec->cmds[i]->in_fd == -1)
// 		return (1);
// 	return (0);
// }

// int	get_word(t_executor *exec, char *word, int i)
// {
// 	exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, word);
// 	if (exec->cmds[i]->simp_cmd == NULL)
// 		return (1);
// 	return (0);
// }

// int	multiple_execution(t_executor *exec, int i)
// {
// 	int		cpid;
// 	int		ends[2];
// 	int		status;
	
// 	if (pipe(ends) == -1)
// 		return (ft_putendl_fd("pipe error", 2), 1);
// 	//ft_putstrarr_fd(exec->cmds[i]->simp_cmd, 1);
// 	cpid = fork();
// 	if (cpid == -1)
// 		return (ft_putendl_fd("fork error", 2), close(ends[0]), close(ends[1]), 1);
// 	if (cpid == 0)
// 	{
// 		child_proc(exec, exec->cmds[i], ends);
// 	}
// 	//printf("Waiting...\n");
// 	waitpid(cpid, &status, 0);
// 	//printf("End Wait\n");
// 	// if (i == exec->num_of_cmds)
// 	// {
// 	// 	if (dup2(ends[1], 1) == -1)
// 	// 		return (ft_putendl_fd("FATAL dup2 error", 2), 1);
// 	// }
// 	if (dup2(ends[0], 0) == -1)
// 		return (ft_putendl_fd("FATAL dup2 error", 2), 1);
// 	if (close(ends[0]) == -1 || close(ends[1]) == -1)
//         return (ft_putendl_fd("FATAL error", 2), 1);
// 	return (WEXITSTATUS(status));
// }

// int	get_outfile_redir(t_executor *exec, char *outfile, t_type type, int i)
// {
// 	if (exec->cmds[i]->outfile != NULL)
// 		free(exec->cmds[i]->outfile);
// 	if (exec->cmds[i]->out_fd != -1 && exec->cmds[i]->out_fd != 1)
// 		close(exec->cmds[i]->out_fd);
// 	exec->cmds[i]->outfile = ft_strdup(outfile);
// 	if (exec->cmds[i]->outfile == NULL)
// 		return (1);
// 	if (type == RE_OUT)
// 		exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false, false);
// 	else
// 		exec->cmds[i]->out_fd = get_fd(exec->cmds[i]->outfile, false, true);
// 	return (0);
// }

// int	get_infile_redir(t_executor *exec, char *infile, int i)
// {
// 	if (exec->cmds[i]->infile != NULL)
// 		free(exec->cmds[i]->infile);
// 	if (exec->cmds[i]->in_fd != -1 && exec->cmds[i]->in_fd != 0)
// 		close(exec->cmds[i]->in_fd);
// 	if (exec->cmds[i]->has_here_doc == true)
// 		unlink(exec->cmds[i]->here_doc);
// 	exec->cmds[i]->has_here_doc = false;
// 	exec->cmds[i]->infile = ft_strdup(infile);
// 	if (exec->cmds[i]->infile == NULL)
// 		return (1);
// 	exec->cmds[i]->in_fd = get_fd(exec->cmds[i]->infile, true, false);
// 	return (0);
// }

// int	get_here_doc(t_executor *exec, char *delim, int i)
// {
// 	if (exec->cmds[i]->infile != NULL)
// 		free(exec->cmds[i]->infile);
// 	if (exec->cmds[i]->in_fd != -1 && exec->cmds[i]->in_fd != 0)
// 		close(exec->cmds[i]->in_fd);
// 	if (exec->cmds[i]->here_doc == NULL)
// 	{
// 		exec->cmds[i]->here_doc = get_temp_name();
// 		if (exec->cmds[i]->here_doc == NULL)
// 			return (1);
// 	}
// 	if (exec->cmds[i]->has_here_doc == true)
// 		unlink(exec->cmds[i]->here_doc);
// 	exec->cmds[i]->has_here_doc = true;
// 	exec->cmds[i]->infile = ft_strdup(exec->cmds[i]->here_doc);
// 	if (exec->cmds[i]->infile == NULL)
// 		return (1); 
// 	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_WRONLY | O_APPEND | O_CREAT, 0777);
//     if (exec->cmds[i]->in_fd == -1)
// 		return (1);
// 	if (handle_here_doc(exec->cmds[i]->in_fd, delim, exec->envp, exec->exit_status) == -1)
// 		return (1);
// 	close(exec->cmds[i]->in_fd);
// 	exec->cmds[i]->in_fd = open(exec->cmds[i]->here_doc, O_RDONLY, 0777);
// 	if (exec->cmds[i]->in_fd == -1)
// 		return (1);
// 	return (0);
// }

// char    *get_temp_name(void)
// {
// 	// char	*temp_name;
// 	char    *temp_str;
// 	// char    *temp_nbr;
// 	int		fd_random;
// 	// int     i;

// 	//temp_str = ".temp";
// 	fd_random = open("/dev/random", O_RDONLY, 0777);
// 	temp_str = (char *)malloc((10 + 1) * sizeof(char));
// 	if (temp_str == NULL)
// 		return (NULL);
// 	if (read(fd_random, temp_str, 10) == -1)
// 		return (close(fd_random), free(temp_str), NULL);
// 	printf("%s\n", temp_str);
// 	return (close(fd_random), temp_str);
	
// 	// temp_nbr = NULL;
// 	// temp_name = NULL;
// 	// i = 0;
// 	// while (i < INT_MAX - 1)
// 	// {
// 	// 	temp_nbr = ft_itoa(i);
// 	// 	if (temp_nbr == NULL)
// 	// 		return (ft_free(temp_nbr), ft_free(temp_name), NULL);
// 	// 	temp_name = ft_strjoin(temp_str, temp_nbr);
// 	// 	if (temp_name == NULL)
// 	// 		return (ft_free(temp_nbr), ft_free(temp_name), NULL);
// 	// 	printf("%s\n", temp_name);
// 	// 	if (access(temp_name, F_OK) == -1)
// 	// 		return (free(temp_nbr), temp_name);
// 	// 	free(temp_nbr);
// 	// 	free(temp_name);
// 	// 	i++;
// 	// }
// 	// return (free(temp_nbr), free(temp_name), NULL);
// }

// int		get_cmds(t_executor *exec, t_list **list, int error_check, int i)
// {
// 	t_list	*cur;

// 	cur = *list;
// 	while (cur)
// 	{
// 		if (cur->type == WORD)
// 		{
// 			error_check = get_word(exec, cur->attr, i);
// 			if (error_check == 1)
// 				return (1);
// 		}
// 		if (cur->type != WORD && cur->type != PIPE)
// 		{
// 			if (cur->type == RE_IN)
// 				error_check = get_infile_redir(exec, cur->next->attr, i);
// 			if (cur->type == RE_OUT || cur->type == APPEND)
// 				error_check = get_outfile_redir(exec, cur->next->attr, cur->type, i);
// 			if (cur->type == HERE_DOC)
// 				error_check = get_here_doc(exec, cur->next->attr, i);
// 			if (error_check == 1)
// 				return (1);
// 			cur = cur->next;
// 		}
// 		if (cur->type == PIPE)
// 			i++;
// 		cur = cur->next;
// 	}
// 	return (0);
// }

// int		get_cmds(t_executor *exec, t_list **list)
// {
// 	t_list	*current;
// 	int	error_check;
// 	int i;

// 	error_check = 0;
// 	i = 0;
// 	current = *list;
// 	while (current)
// 	{
// 		if (current->type == WORD)
// 		{
// 			exec->cmds[i]->simp_cmd = ft_stradd_tostrarr(exec->cmds[i]->simp_cmd, current->attr);
// 			if (exec->cmds[i]->simp_cmd == NULL)
// 				return (1);
// 		}
// 		if (current->type == RE_IN)
// 		{
// 			current = current->next;
// 			error_check = get_infile_redir(exec, current->attr, i);
// 			if (error_check == 1)
// 				return (1); 
// 		}
// 		if (current->type == RE_OUT || current->type == APPEND)
// 		{
// 			current = current->next;
// 			error_check = get_outfile_redir(exec, current->attr, current->type, i);
// 			if (error_check == 1)
// 				return (1);
// 		}
// 		if (current->type == HERE_DOC)
// 		{
// 			current = current->next;
// 			error_check = get_here_doc(exec, current->attr, i);
// 			if (error_check == 1)
// 				return (1);
// 		}
// 		if (current->type == PIPE)
// 		{
// 			exec->cmds[i]->cmd_nbr = i;
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

// int	multiple_execution(t_executor *exec, int i)
// {
// 	pid_t	cpid;
// 	int		ends[2];
// 	int		status;
	
// 	if (pipe(ends) == -1)
// 		return (ft_putendl_fd("pipe error", 2), 1);
// 	cpid = fork();
// 	if (cpid == -1)
// 		return (ft_putendl_fd("fork error", 2), close(ends[0]), close(ends[1]), 1);
// 	if (cpid == 0)
// 		child_proc(exec, exec->cmds[i], ends);
// 	printf("Waiting...\n");
// 	waitpid(cpid, &status, 0);
// 	printf("End Wait\n");
// 	if (dup2(ends[0], 0) == -1)
// 		return (-1);
// 	close(ends[0]);
// 	close(ends[1]);
// 	return (0);
// }

// int	multiple_execution(t_executor *exec)
// {
// 	int	i;
// 	int	status;

// 	i = 0;
// 	while (i < exec->num_of_pipes)
// 	{
// 		printf("Pipe number %d\n", i + 1);
// 		if (pipe(exec->pipes[i]) == -1)
// 			return (1);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < exec->num_of_pipes)
// 	{
// 		exec->cpids[i] = fork();
// 		if (exec->cpids[i] == -1)
// 			return (close(exec->pipes[i][0]), close(exec->pipes[i][1]), 1);
// 		if (exec->cpids[i] == 0)
// 			child_proc(exec, exec->cmds[i], exec->pipes[i]);
// 		close(exec->pipes[i][0]);
// 		close(exec->pipes[i][1]);
// 		printf("Waiting...\n");
// 		waitpid(exec->cpids[i], NULL, 0);
// 		i++;
// 	}
// 	exec->cpids[i] = fork();
// 	if (exec->cpids[i] == -1)
// 		return (close(exec->pipes[i][0]), close(exec->pipes[i][1]), 1);
// 	if (exec->cpids[i] == 0)
// 		child_proc(exec, exec->cmds[i], exec->pipes[i]);
// 	close(exec->pipes[exec->num_of_pipes - 1][0]);
// 	close(exec->pipes[exec->num_of_pipes - 1][1]);
// 	waitpid(exec->cpids[exec->num_of_pipes - 1], &status, 0);
// 	printf("End Waiting\n");
// 	return (0);
// }

// int	main(int argc, char *argv[], char *env[])
// {
// 	t_minishell	ms;
	
// 	if (argc != 1)
// 		return (1);
// 	if (initialize_minishell(&ms, argc, argv, env) == 1)
// 		return (1);
// 	while (true)
// 	{
// 		error_check = read_input(&ms);
// 		if (error_check == 1)
// 			return (free_lexer(ms.lex), ft_free_strarr(ms.envp), rl_clear_history(), 1);
// 		if (error_check == 2)
// 		{
// 			free_lexer(ms.lex);
// 			continue ;
// 		}
// 		if (parse_input(&ms) == 1)
// 			return (free_lexer(ms.lex), free_executor(ms.exec), ft_free_strarr(ms.envp), rl_clear_history(), 1);
// 		//same check as above but we have no lines :c
// 		free_lexer(ms.lex);
// 		if (execute_input(&ms) == 1)
// 			return (free_executor(ms.exec), ft_free_strarr(ms.envp), 1);
// 		free_executor(ms.exec);
// 	}
// 	return (0);
// }

// int	multiple_execution(t_executor *exec)
// {
// 	int	i;
// 	int	status;
// 	int	ends[2];

// 	i = 0;
// 	while (i < exec->num_of_pipes)
// 	{
// 		if (pipe(ends) == -1)
// 			return (1);
// 		exec->cpids[i] = fork();
// 		if (exec->cpids[i] == -1)
// 			return (close(ends[0]), close(ends[1]), 1);
// 		if (exec->cpids[i] == 0)
// 			child_proc(exec, exec->cmds[i], ends);
// 		exec->cpids[i + 1] = fork();
// 		if (exec->cpids[i + 1] == -1)
// 			return (close(ends[0]), close(ends[1]), 1);
// 		if (exec->cpids[i + 1] == 0)
// 			child_proc(exec, exec->cmds[i + 1], ends);
// 		close(ends[0]);
// 		close(ends[1]);
// 		waitpid(exec->cpids[i], NULL, 0);
// 		waitpid(exec->cpids[i + 1], &status, 0);
// 		i++;
// 	}
// 	return (0);
// }

// char	*get_cmd_path(t_executor *exec, t_cmd *cmd)
// {
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	while (exec->paths[i] != NULL)
// 	{
// 		printf("Child: Path finding\n");
// 		temp = ft_strjoin(exec->paths[i], "/");
// 		if (temp == NULL)
// 			return (NULL);
// 		printf("Child: temp = %s\n", temp);
// 		printf("Child: Joing\n");
// 		printf("Child: simp_cmd[0] = %s\n", cmd->simp_cmd[0]);
// 		cmd->cmd_path = ft_strjoin(temp, cmd->simp_cmd[0]);
// 		if (cmd->cmd_path == NULL)
// 			return (ft_free(temp), free_executor(exec), NULL);
// 		printf("Child: Free temp\n");
// 		ft_free(temp);
// 		printf("Child: Check for access\n");
// 		if (access(cmd->cmd_path, F_OK | X_OK) == 0)
// 			return (cmd->cmd_path);
// 		ft_free(cmd->cmd_path);
// 		i++;
// 	}
// 	return (cmd->simp_cmd[0]);
// }

// int	execute_input(t_minishell *ms)
// {
// 	if (initialize_executor_2(ms) == 1)
// 		return (1);
// 	if (ms->exec->num_of_cmds == 1)
// 	{
// 		printf("Start execution\n");
// 		if (single_execution(ms->exec) == 1)
// 			return (1);
// 	}
// 	// else
// 	// {
// 	// 	if (piping(ms->exec) == 1)
// 	// 		return (1);
// 	// }
// 	return (0);
// }

// int	single_execution(t_executor *exec)
// {
// 	int	status;

// 	printf("Forking:\n");
// 	exec->cpids[0] = fork();
// 	if (exec->cpids[0] == -1)
// 		return (1);
// 	if (exec->cpids[0] == 0)
// 		single_child_proc(exec, exec->cmds[0]);
// 	printf("Parent: Waiting\n");
// 	waitpid(exec->cpids[0], &status, 0);
// 	//free_exec(exec);
// 	//change last cmd status in ms
// 	//exit(WEXITSTATUS(status));
// 	return (0);
// }

// void	single_child_proc(t_executor *exec, t_cmd *cmd)
// {	
// 	printf("Child: Start\n");
// 	if (cmd->infile != NULL)
// 	{
// 		printf("Child: infile_fd dup\n");
// 		if (dup2(cmd->in_fd, 0) == -1)
// 		{
// 			ft_putendl_fd("dup2 failed", 2);
// 			//free();
// 			exit(1);
// 		}
// 		close(cmd->in_fd);
// 	}
// 	if (cmd->outfile != NULL)
// 	{
// 		printf("Child: outfile_fd dup\n");
// 		if (dup2(cmd->out_fd, 1) == -1)
// 		{
// 			ft_putendl_fd("dup2 failed", 2);
// 			//free();
// 			exit(1);
// 		}
// 		close(cmd->out_fd);
// 	}
// 	if (exec->paths != NULL)
// 	{
// 		printf("Child: Get the cmd_path\n");
// 		cmd->cmd_path = get_cmd_path(exec, exec->cmds[0]);
// 		if (cmd->cmd_path == NULL)
// 			exit_with_error("malloc error", exec);
// 		printf("Child: cmd_path = %s\n", cmd->cmd_path);
// 	}
// 	printf("Child: Enters execution function\n");
// 	execute_cmd(exec, exec->cmds[0]);
// }

// void	execute_cmd(t_executor *exec, t_cmd *cmd)
// {
// 	if (cmd->cmd_path == NULL)
// 	{
// 		printf("Child: path env does not exists\n");
// 		ft_free_strarr(exec->envp);
// 		free_executor(exec);
// 		exit(127);
// 	}
// 	printf("Child: execute cmd\n");
// 	if (execve(cmd->cmd_path, cmd->simp_cmd, exec->envp) == -1)
// 	{
// 		ft_putstr_fd(cmd->cmd_path, 2);
// 		ft_putendl_fd(": command not found", 2);
// 		ft_free_strarr(exec->envp);
// 		free_executor(exec);
// 		exit(127);
// 	}
// }

// int	read_input(t_minishell *ms)
// {
// 	if (initialize_lexer(ms) == 1)
// 		return (1);
// 	while (true)
// 	{	
// 		ms->lex->input = readline("./minishell$ ");
// 		if (ms->lex->input == NULL)
// 			return (1);
// 		if (ft_isspace_str(ms->lex->input) == false)
// 			break ;
// 	}
// 	add_history(ms->lex->input);
// 	if (ft_strncmp(ms->lex->input, "exit", 4) == 0)
// 		free_and_exit(ms);
// 	if (tokenize_input(ms->lex) == 1)
// 		return (1);
// 	if (check_for_expansion(&ms->lex->token_list, ms->envp) == 1)
// 		return (1);
// 			// printf("After expansion: \n");
// 			// ft_putlst_fd(ms->lex->token_list, 1);
// 	if (check_for_dequotation(&ms->lex->token_list) == 1)
// 		return (1);
// 			printf("After dequotation: \n");
// 			ft_putlst_fd(ms->lex->token_list, 1);
// 	//parse_tokens_to_struct(ms);
// 	return (0);
// }

// char	*handle_expansion(t_list *node, char **envp, int *i)
// {
// 	int		len;
// 	int		pos;
// 	int		j;

// 	if (ft_isspace(node->attr[*i + 1]) == true || node->attr[*i + 1] == '\0'
// 		|| node->attr[*i + 1] == '?' || node->attr[*i + 1] == '$'
// 		|| node->attr[*i + 1] == '"' || node->attr[*i + 1] == '\'')
// 		return (node->attr);
// 	pos = *i + 1; //pos == c after $
// 	len = 0;
// 	while (node->attr[*i] != '\0' && ft_isspace(node->attr[*i]) == false && node->attr[*i] != '\'' && node->attr[*i] != '"')
// 	{
// 		if (node->attr[*i + 1] == '$')
// 		{
// 			len++;
// 			break ;
// 		}
// 		*i = *i + 1;
// 		len++;
// 	}
// 	if (node->attr[*i] == '\'' || node->attr[*i] == '"')
// 		handle_quotes_in_expansion(node, node->attr[*i]);
// 	if (node->in_squotes == true)
// 		return (node->attr);
// 	j = 0;
// 	while (envp[j] != NULL)
// 	{
// 		if (ft_strncmp(envp[j], node->attr + pos, len - 1) == 0)
// 			return (*i = -1, node->in_dquotes = false, node->in_squotes = false, \
// 			handle_valid_expansion(node->attr, envp[j], len, pos));
// 		j++;
// 	}
// 	return (*i = -1, node->in_dquotes = false, node->in_squotes = false, \
// 	handle_invalid_expansion(node->attr, len));
// }

// int	check_for_expansion(t_list **token_list, char **envp, int exit_code)
// {
// 	t_list	*current_node;

// 	current_node = *token_list;
// 	while (current_node != NULL)
// 	{
// 		if (current_node->type == WORD)
// 		{
// 			if (ft_strchr(current_node->attr, '$') != NULL)
// 			{
// 				current_node->attr = handle_expansion(current_node->attr, envp, 0);
// 				if (current_node->attr == NULL)
// 					return (1);
// 			}
// 		}
// 		current_node = current_node->next;
// 	}
// 	return (0);
// }

// char	*handle_expansion(char *to_expand, char **envp, int i)
// {
// 	int		len;
// 	int		pos;
// 	int		j;

// 	while (to_expand[i] != '$' && to_expand[i] != '\0')
// 		i++;
// 	if (ft_isspace(to_expand[i + 1]) == true || to_expand[i + 1] == '\0'
// 		|| to_expand[i + 1] == '\'' || to_expand[i + 1] == '"'
// 		|| to_expand[i + 1] == '?' || to_expand[i + 1] == '$')
// 		return (to_expand);
// 	pos = i + 1;
// 	len = 0;
// 	while (to_expand[i] != '\0' && ft_isspace(to_expand[i]) == false
// 		&& to_expand[i] != '\'' && to_expand[i] != '"')
// 	{
// 		i = i + 1;
// 		len++;
// 	}
// 	j = -1;
// 	while (envp[++j] != NULL)
// 	{
// 		if (ft_strncmp(envp[j], to_expand + pos, len - 1) == 0)
// 			return (handle_valid_expansion(to_expand, \
// 				envp[j], len, pos));
// 	}
// 	return (handle_invalid_expansion(to_expand, len));
// }

// t_type	get_redir_type(t_lexer *lex)
// {
// 	t_type	type;

// 	if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] != '<')
// 		type = RE_IN;
// 	if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] != '>')
// 		type = RE_OUT;
// 	lex->i++;
// 	if (lex->input[lex->i] == '<' && lex->input[lex->i - 1] == '<')
// 	{
// 		type = HERE_DOC;
// 		lex->i++;
// 	}
// 	if (lex->input[lex->i] == '>' && lex->input[lex->i - 1] == '>')
// 	{
// 		type = APPEND;
// 		lex->i++;
// 	}
// 	return (type);
// }

// size_t	ft_strlen_except(const char *str, char *exceptions)
// {
// 	size_t	len;
// 	bool	is_except;
// 	int		i;
// 	int		j;

// 	len = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		is_except = false;
// 		j = 0;
// 		while (exceptions[j] != '\0')
// 		{
// 			if (str[i] == exceptions[j])
// 				is_except = true;
// 			j++;
// 		}
// 		if (is_except == false)
// 			len++;
// 		i++;
// 	}
// 	return (len);
// }

// char	*handle_expansion(char *to_expand, char **envp, int *i)
// {
// 	int		len;
// 	int		pos;
// 	int		j;
// 	//int		quote;
	
// 	if (ft_isspace(to_expand[*i + 1]) == true || to_expand[*i + 1] == '\0'
// 		|| to_expand[*i + 1] == '\'' || to_expand[*i + 1] == '"'
// 		|| to_expand[*i + 1] == '?')
// 		return (*i = *i + 1, to_expand);
// 	pos = *i + 1;
// 	len = 0;
// 	while (to_expand[*i] != '\0' && ft_isspace(to_expand[*i]) == false
// 		&& to_expand[*i] != '\'' && to_expand[*i] != '"')
// 	{
// 		*i = *i + 1;
// 		len++;
// 	}
// 	// quote = 0;
// 	// if (to_expand[*i] == '\'' || to_expand[*i] == '"')
// 	// 	quote = 1;
// 	// printf("%s\n", to_expand + pos);
// 	// printf("To read chars: %d\n", len - 1);// - quote);
// 	j = -1;
// 	while (envp[++j] != NULL)
// 	{
// 		//if (ft_strnstr(envp[j], to_expand + pos, len - 1) != NULL) //&& envp[j][len - 1] == '=')
// 		if (ft_strncmp(envp[j], to_expand + pos, len - 1) == 0)
// 		{
// 			// printf("%s\n", "Found");
// 			return (*i = 0, handle_valid_expansion(to_expand, envp[j], len, pos));
// 		}
// 	}
// 	// printf("Never found\n");
// 	return (*i = 0, handle_invalid_expansion(to_expand, len));
// }

// char	*handle_valid_expansion(char *to_expand, char *env, int len, int pos)
// {
// 	char	*exp_str;
// 	char	*exp_var;
// 	int		i;
// 	int		j;
	
// 	// ft_putendl_fd(env, 1);
// 	// ft_putendl_fd(env + len, 1);
// 	exp_var = ft_substr(env, len, ft_strlen(env) - len);
// 	if (exp_var == NULL)
// 		return (NULL);
// 	// printf("LEN: %d\n", len);
// 	// ft_putendl_fd(exp_var, 1);
// 	exp_str = (char *)malloc(((ft_strlen(to_expand) - len + ft_strlen(exp_var) + 1) * sizeof(char)));
// 	if (exp_str == NULL)
// 		return (free(exp_var), NULL);
// 	i = 0;
// 	j = 0;
// 	while (to_expand[j] != '\0' && to_expand[j] != '$')
// 		exp_str[i++] = to_expand[j++];
// 	j = 0;
// 	while (exp_var[j] != '\0')
// 		exp_str[i++] = exp_var[j++];
// 	j = pos + len - 1;
// 	while (to_expand[j] != '\0')
// 		exp_str[i++] = to_expand[j++];
// 	exp_str[i] = '\0';
// 	// ft_putendl_fd(exp_str, 1);
// 	return (free(to_expand), free(exp_var), exp_str);
// }

// int	get_cmds(t_executor *exec, t_list **list)
// {

// 	t_list	*current;
// 	//bool	has_wrd;
// 	int 	i;

// 	printf("Number of cmds: %d\n", exec->num_of_cmds);
// 	i = 0;
// 	current = *list;
// 	printf("test0\n");
// 	while (current && current->next) //&& i < ms->cmds->num_of_simp_cmds + 1)
// 	{
// 		//exec->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
// 		initialize_cmd(exec->cmds[i], i);
// 		//NULL CHECK
// 		// cmds->simp_cmd = malloc(sizeof(char *) * (ms->cmds->num_of_args + 1));
// 		// if (!cmds->simp_cmd)
// 		// 	return (NULL);
// 		//has_wrd = false;
// 		while (current->next != NULL && current->type != PIPE)
// 		{
// 			if (current->type == WORD)
// 			{
// 				has_wrd = true;
// 				ms->cmds[i]->simp_cmd = ft_stradd_tostrarr(ms->cmds[i]->simp_cmd, current->attr);
// 				if (!ms->cmds)
// 					return (1); //free)
// 				ft_putstrarr_fd(ms->cmds[i]->simp_cmd, 1);
// 			}
// 			// else if (current->type == RE_IN)
// 			// 	ms->cmd->infile = current->next->attr;
// 			// else if (current->type == RE_OUT)
// 			// 	ms->cmd->outfile = current->next->attr;
// 			//NULL CHECK
// 			current = current->next;
// 		}
// 		current = current->next;
// 		i++;
// 	}
// 	// if (has_wrd == false)
// 	// 	return (ft_error("parse error: need at least one word"), 1);
// 	return (0);
// }



// bool is_valid_input(t_lexer *lex)
// {
// 	t_list *head;
// 	t_list *current;

// 	head = lex->token_list;
// 	current = lex->token_list;
// 	while (current != NULL)
// 	{
// 		if (current->type == RE_IN && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `<'"), false);
// 		if (current->type == RE_OUT && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `>'"), false);
// 		if (current->type == HERE_DOC && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `<<'"), false);
// 		if (current->type == APPEND && current->next != NULL && current->next->type != WORD)
// 			return (ft_error("parse error near `>>'"), false);
// 		if (current->type != WORD && current->next == NULL)
// 			return (ft_error("word token required as last input"), false);
// 		current = current->next;
// 	}
// 	lex->token_list = head;
// 	return (true);
// }

// t_list	*get_redir_token_old(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	t_type	type;
// 	char	*attr;
// 	int		j;

// 	type = get_redir_type(lex);
// 	while (ft_isspace(lex->input[lex->i]) == true)
// 		lex->i++;
// 	if (lex->input[lex->i] == '\0')
// 		return (NULL);
// 	j = 0;
// 	while (lex->input[lex->i] != '\0')
// 	{
// 		if (ft_isspace(lex->input[lex->i]) == true || lex->input[lex->i] == '<' 
// 			|| lex->input[lex->i] == '>' || lex->input[lex->i] == '|')
// 			break ;
// 		lex->i++;
// 		j++;
// 	}
// 	attr = (char *)malloc((j + 1) * sizeof(char));
// 	if (attr == NULL)
// 		return (NULL);
// 	ft_strlcpy(attr, lex->input + (lex->i - j), j + 1);
// 	new_token = ft_lstnew(type, attr);
// 	return (new_token);
// }

// int	lex_input_old(t_lexer *lex)
// {
// 	t_list	*new_token;

// 	while (lex->input[lex->i] != '\0')
// 	{
// 		while (ft_isspace(lex->input[lex->i]) == true)
// 			lex->i++;
// 		if (lex->input[lex->i] == '|')
// 		{	
// 			new_token = ft_lstnew(PIPE, "|");
// 			lex->i++;
// 		}
// 		else if (lex->input[lex->i] == '<' || lex->input[lex->i] == '>')		
// 			new_token = get_redir_token(lex);
// 		else 
// 			new_token = get_word_token(lex);
// 		if (new_token == NULL)
// 		{
// 			if (lex->token_list != NULL)
// 				ft_lstclear(&lex->token_list);
// 			return (1);
// 		}
// 		ft_lstadd_back(&lex->token_list, new_token);
// 	}
// 	return (0);
// }

// void	expand_env(t_lexer *lex, t_list **lst)
// {
// 	t_list	*temp;

// 	temp = *lst;
// 	if (lst == NULL)
// 		return ;
// 	while (temp != NULL)
// 	{
// 		if (temp->type == 1 && ft_strchr(temp->attr, '$'))
// 			temp->attr = handle_expansion(lex, temp->attr);
// 		temp = temp->next;
// 	}
// }

// t_list	*handle_quotes(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	char	*attr;
// 	char	quote;
// 	bool	is_closed;
// 	int		len;

// 	if (lex->input[lex->i] == '\"')
// 		quote = '\"';
// 	else
// 		quote = '\'';
// 	is_closed = false;
// 	lex->i++;
// 	len = 1;
// 	while (lex->input[lex->i] != '\0')
// 	{
// 		if (lex->input[lex->i] == quote)
// 			is_closed = true;
// 		lex->i++;
// 		len++;
// 	}
// 	// if (is_closed == false)
// 	// 	return (NULL);
// 	attr = (char *)malloc((len + 2) * sizeof(char));
// 	if (attr == NULL)
// 		return (NULL);
// 	ft_strlcpy(attr, lex->input + (lex->i - 1 - len), len + 2);
// 	new_token = ft_lstnew(WORD, attr);
// 	return (new_token);
// }

// t_list	*get_word_token2(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	char	*attr;
// 	int		len;

// 	attr = NULL;
// 	len = 0;
// 	while (lex->input[lex->i] != '\0')
// 	{
// 		// if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
// 		// 	return (handle_quotes(lex));
// 		if (ft_isspace(lex->input[lex->i]) == true
// 			|| is_token(lex->input[lex->i]) == true)
// 			//|| lex->input[lex->i] == '"' || lex->input[lex->i] == '\'')
// 			break ;
// 		if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
// 			return (handle_quotes(lex));
// 		lex->i++;
// 		len++;
// 	}
// 	attr = (char *)malloc((len + 1) * sizeof(char));
// 	if (attr == NULL)
// 		return (NULL);
// 	ft_strlcpy(attr, lex->input + (lex->i - len), len + 1);
// 	new_token = ft_lstnew(WORD, attr);
// 	return (new_token);
// }
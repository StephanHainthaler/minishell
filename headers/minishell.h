/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:26 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/23 09:01:00 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef struct s_lexer
{
	t_list	*token_list;
	char	*input;
	int		i;
	char	**envp;
}			t_lexer;

typedef struct s_cmd
{
    char	**simp_cmd;
    char	*cmd_path;
    char	*infile;
    char	*outfile;
	char	*here_doc;
    int		in_fd;
    int		out_fd;
    int		cmd_nbr;
	bool	has_here_doc;
}			t_cmd;

typedef struct s_executor
{
	t_cmd	**cmds;
	int		num_of_cmds;
	int		num_of_pipes;
	char	**paths;
	bool	is_path_set;
	int		exit_status;
	char	**envp;
}			t_executor;

typedef struct s_minishell
{
	t_lexer		*lex;
	t_executor	*exec;
	int			last_exit_code;
	int			argc;
	char		**argv;
	char		**envp;
}				t_minishell;

extern int	global_state;

//initialization.c 
int		initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[]);
int		initialize_lexer(t_minishell *ms);
int		initialize_executor(t_minishell *ms);
int		initialize_executor_2(t_minishell *ms, int i);
t_cmd	*initialize_cmd(t_cmd *cmd, int cmd_nbr);

//lexer.c
int		read_input(t_minishell *ms);
int		tokenize_input(t_lexer *lex);
bool	is_token(char c);
t_list	*get_word_token(t_lexer *lex, int *error);
t_list	*get_non_word_token(t_lexer *lex);

//expansion.c
int		check_for_expansion(t_list **token_list, char **envp, int ec);
char	*handle_expansion(t_list *node, char **envp, int exit_code, int *i);
char	*handle_valid_expansion(char *to_expand, char *env, int len, int pos);
char	*handle_invalid_expansion(char *str, int len, int pos);
char	*handle_exit_code_expansion(char *to_expand, int exit_code, int *i);

//expansion_utils.c
int		get_envname_len(char *str, int *i);
bool	check_for_env(char *str1, char *str2, int len);
bool	is_str_expandable(char *str);

//quotation.c
int		check_for_dequotation(t_list **token_list);
int		handle_quotes(t_lexer *lex, char quote, int *len);
char	*handle_dequotation(char *to_trim, int i, int j);
int		get_dequoted_strlen(char *str);
void	handle_quotes_in_expansion(t_list *node, char quote);

//parser.c
int		parse_input(t_minishell *ms);
bool	is_valid_input(t_lexer *lex);
int		count_cmds(t_list **list);
int		get_cmds(t_executor *exec, t_list **list, int error_check, int i);
void	ft_print_cmd(t_cmd *cmd);

//parser_utils.c
int		get_word(t_executor *exec, char *word, int i);
int		get_outfile_redir(t_executor *exec, char *outfile, t_type type, int i);
int		get_infile_redir(t_executor *exec, char *infile, int i);
int		get_here_doc(t_executor *exec, char *delim, int i);

//here_doc.c
int 	handle_here_doc(int here_doc_fd, char *delim, char **envp, int exit_code);
char	*check_for_here_doc_expansion(char *str, char **envp, int ec);
char    *expand_here_doc(char *str, char **envp, int exit_code, int *i);
char    *get_temp_name(void);
char    *get_random_temp_name(void);

//executor.c
int		execute_input(t_minishell *ms);
int		single_execution(t_executor *exec);
int		multiple_execution(t_executor *exec);
int		multi_pipe(t_executor *exec, int *prevpipe, int i);
int		last_pipe(t_executor *exec, int prevpipe, int i);
void	execute_cmd(t_executor *exec, t_cmd *cmd);

//executor_utils.c
char	**get_paths(t_executor *exec, int *error_flag);
char	*get_cmd_path(t_executor *exec, t_cmd *cmd);
int		get_fd(char *file, bool is_in_fd, bool is_append);
bool	is_path_set(char *envp[]);
int		handle_redirection(t_cmd *cmd);
int		handle_redirection_2(t_cmd *cmd, int re_in, int re_out);

//child.c
void	child_proc(t_executor *exec, t_cmd *cmd, int ends[]);
void	single_child_proc(t_executor *exec, t_cmd *cmd);
void	multi_child_proc(t_executor *exec, t_cmd *cmd, int ends[], int *old_end);
void	last_child_proc(t_executor *exec, t_cmd *cmd, int old_end);
void	exit_child(t_executor *exec, int end1, int end2, int exit_status);

//builtins_1.c
int		handle_builtin(char **simp_cmd, t_executor *exec);
int		handle_builtins_non_pipable(t_minishell *ms);

//builtins_2.c
void	ft_echo(char **simp_cmd);
void	ft_cd(char **simp_cmd);
void	ft_pwd(char **simp_cmd);
char	**ft_export(char **simp_cmd, char **envp);
char	**ft_unset(char **simp_cmd, char **envp);

//builtins_utils.c
int		sort_strarray(char **strarray);
bool	ft_are_str_indentical(char *str1, char *str2);
bool	is_replacable(char *str1, char *str2);

//signals.c
void	handle_signal(int sig_num);

//free.c
void	free_lexer(t_lexer *lex);
void	free_executor(t_executor *exec);
void	free_cmds(t_cmd **cmds, int num_of_cmds);
void	free_cmd(t_cmd *cmd);
void	free_and_exit(t_minishell *ms);

#endif

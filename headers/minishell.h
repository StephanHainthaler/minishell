/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:07:42 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/16 15:44:35 by shaintha         ###   ########.fr       */
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

extern int	g_code;

typedef struct s_lexer
{
	t_list	*token_list;
	char	*input;
	bool	in_squotes;
	bool	in_dquotes;
	size_t	i;
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
	bool	is_parent;
}			t_cmd;

typedef struct s_executor
{
	t_cmd	**cmds;
	int		num_of_cmds;
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

//initialization.c

int		initialize_minishell(t_minishell *ms, int argc,
			char *argv[], char *env[]);
int		initialize_lexer(t_minishell *ms);
int		initialize_executor(t_minishell *ms);
int		initialize_executor_2(t_minishell *ms);
t_cmd	*initialize_cmd(t_cmd *cmd, int cmd_nbr);

//environment.c

char	**increase_shlvl(char **envp);
bool	is_env_set(char *envp[], char *env_name);
char	*get_env_var(char **envp, char *env_name);
size_t	get_env_var_pos(char **envp, char *env_name);

//lexer.c

int		get_input(t_minishell *ms);
int		read_input(t_lexer *lex);
int		tokenize_input(t_lexer *lex);

//lexer_utils.c

bool	is_token(char c);
t_list	*get_word_token(t_lexer *lex, int *error);
t_list	*get_non_word_token(t_lexer *lex);

//expansion.c

int		check_for_expansion(t_list **token_list, char **envp, int ec);
char	*handle_expansion(t_list *node, char **envp, int exit_code, size_t *i);
char	*handle_valid_expansion(char *to_expand, char *env,
			size_t len, size_t pos);
char	*handle_invalid_expansion(char *str, size_t len, size_t pos);
char	*handle_exit_code_expansion(char *to_expand, int exit_code, size_t *i);

//expansion_utils.c

int		handle_special_expansion(t_list *node, int exit_code, size_t *i);
size_t	get_envname_len(char *str, size_t *i);
size_t	get_envvar_len(char *envvar);
bool	check_for_env(char *str1, char *str2, size_t len);

//quotation.c

char	*dequote(char *str);
int		get_dequoted_strlen(char *str);
int		handle_quote_closure(t_lexer *lex, char quote, size_t *len);
void	handle_quotes_in_expansion(t_list *node, char quote);

//parser.c

int		parse_input(t_minishell *ms);
int		count_cmds(t_list **list);
bool	is_valid_input(t_lexer *lex);
int		get_cmds(t_executor *exec, t_list **list, int error_check, size_t i);

//parser_utils.c

int		get_word(t_executor *exec, char *word, size_t i);
int		get_outfile_redir(t_executor *exec, char *outfile,
			t_type type, size_t i);
int		get_infile_redir(t_executor *exec, char *infile, size_t i);
int		get_here_doc(t_executor *exec, char *delim, size_t i);
bool	is_file_ambigious(char *file);

//here_doc.c

int		handle_here_doc(int here_doc_fd, char *delim, t_executor *exec);
int		read_here_doc(int here_doc_fd, char *delim,
			char *deq_delim, t_executor *exec);
char	*get_random_temp_name(void);
char	*check_here_doc_expansion(char *str, char *delim, char **envp, int ec);
char	*expand_here_doc(char *str, char **envp,
			int exit_code, size_t *i);

//executor.c

int		execute_input(t_minishell *ms);
int		single_execution(t_executor *exec);
int		multiple_execution(t_executor *exec);
int		multi_pipe(t_executor *exec, int *prevpipe, int i);
int		last_pipe(t_executor *exec, int prevpipe, int i);

//executor_utils.c

char	**get_paths(t_executor *exec, int *error_flag);
int		get_fd(char *file, bool is_in_fd, bool is_append);
char	*get_cmd_path(t_executor *exec, t_cmd *cmd,
			int *error_flag, size_t i);
bool	is_cmd_path_special_case(char *cmd_path, t_executor *exec);
int		handle_redirection(t_cmd *cmd, int in, int out);

//child.c

void	execute_cmd(t_executor *exec, t_cmd *cmd);
void	single_child_proc(t_executor *exec, t_cmd *cmd);
void	multi_child_proc(t_executor *exec, t_cmd *cmd,
			int ends[], int *old_end);
void	last_child_proc(t_executor *exec, t_cmd *cmd, int old_end);
void	exit_child(t_executor *exec, int end1, int end2, int exit_status);

//builtins_1.c

int		handle_builtins_1(t_executor *exec, char **simp_cmd);
int		handle_builtins_2(t_executor *exec, char **simp_cmd);
int		handle_builtins_non_pipable(t_minishell *ms, char **simp_cmd);
int		ft_exit(t_minishell *ms, char **simp_cmd);
void	ft_env(char **simp_cmd, char **envp, t_executor *exec);

//builtins_2.c

void	ft_echo(char **simp_cmd, t_executor *exec);
int		ft_cd(char **simp_cmd, char **envp, t_executor *exec);
int		ft_pwd(t_executor *exec);
char	**ft_export(char **simp_cmd, char **envp, t_executor *exec, size_t i);
char	**ft_unset(char **simp_cmd, char **envp, t_executor *exec, size_t i);

//builtins_utils_1.c

int		get_exitcode(char **simp_cmd, int last_exit_code);
int		print_declare(char **strarr);
bool	is_replacable(char *str1, char *str2);
bool	is_exportable(char *to_export, t_executor *exec, size_t *i);
bool	is_valid_identifier(char *to_export);

//builtins_utils_2.c

int		change_to_home_directory(char **simp_cmd,
			char **envp, t_executor *exec);
int		change_to_other_directory(char **simp_cmd,
			char **envp, t_executor *exec);
char	**update_pwds(char **envp, char *pwd, char *oldpwd);
char	**update_pwd(char **envp, char *pwd);
char	**update_oldpwd(char **envp, char *oldpwd);

//builtins_utils_3.c

size_t	parse_flag_n(char **simp_cmd, size_t *flag_n);
void	print_echo(char **simp_cmd, size_t start_index, size_t flag_n);

//signals.c

void	signals(int mode);
void	signals_interactive(void);
void	signals_subshell(void);
void	signals_heredoc(void);

//signal_handler.c

void	sigint_interactive(int sig_num);
void	sigint_subshell(int sig_num);
void	sigint_heredoc(int sig_num);
void	handle_sigquit(int sig_num);

//free.c

void	free_lexer(t_lexer *lex);
void	free_executor(t_executor *exec);
void	free_cmds(t_cmd **cmds, int num_of_cmds);
void	free_cmd(t_cmd *cmd);

#endif

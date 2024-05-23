/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:26 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/23 14:40:22 by juitz            ###   ########.fr       */
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
    int		in_fd;
    int		out_fd;
    int		cmd_nbr;
}            t_cmd;

typedef struct s_executor
{
	t_cmd	**cmds;
	int		num_of_cmds;
	int		num_of_pipes;
	char	**paths;
	int		**pipes;
	pid_t	*cpids;
	char	**envp;
}			t_executor;

typedef struct s_minishell
{
	t_lexer		*lex;
	t_executor	*exec;
	int			argc;
	char		**argv;
	char		**envp;
}				t_minishell;

//initialization.c 
int		initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[]);
int		initialize_lexer(t_minishell *ms);
int		initialize_executor(t_minishell *ms);
t_cmd	*initialize_cmd(t_cmd *cmd, int cmd_nbr);

//lexer.c
int		read_input(t_minishell *ms);
int		tokenize_input(t_lexer *lex);
bool	is_token(char c);
t_list	*get_word_token(t_lexer *lex);
t_list	*get_non_word_token(t_lexer *lex);

//expansion.c
int		check_for_expansion(t_list **token_list, char **envp);
char	*handle_expansion(t_list *node, char **envp, int *i);
char	*handle_valid_expansion(char *to_expand, char *env, int len, int pos);
char	*handle_invalid_expansion(char *str, int len, int pos);
int		get_envname_len(t_list *node, int *i);

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
int		count_cmds(t_list **list);
int		get_cmds(t_executor *exec, t_list **list);

//free.c
void	free_minishell(t_minishell *ms);
void	free_lexer(t_lexer *lex);
void	free_executor(t_executor *exec);
void	free_cmds(t_cmd **cmds, int	num_of_cmds);
void	free_and_exit(t_minishell *ms);

#endif

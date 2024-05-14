/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:26 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/14 12:21:33 by shaintha         ###   ########.fr       */
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

typedef struct s_minishell
{
	t_lexer	*lex;
	int		argc;
	char	**argv;
	char	**envp;
}			t_minishell;

//initialization.c 
int		initialize_minishell(t_minishell *ms, int argc, char *argv[], char *env[]);
int		initialize_lexer(t_minishell *ms);

//lexer.c
int		read_input(t_minishell *ms);
int		tokenize_input(t_lexer *lex);
bool	is_token(char c);
t_list	*get_word_token(t_lexer *lex);
t_list	*get_non_word_token(t_lexer *lex);

//expansion.c
int		check_for_expansion(t_list **token_list, char **envp);
char	*handle_expansion(t_list *node, char **envp, int *i, char quote);
char	*handle_valid_expansion(char *to_expand, char *env, int len, int pos);
char	*handle_invalid_expansion(char *str, int len);
char	handle_quotes_in_expansion(t_list *node, char quote);

//quotation.c
int		check_for_dequotation(t_list **token_list);
int		handle_quotes(t_lexer *lex, char quote, int *len);
char	*handle_dequotation(char *to_trim, int i, int j);
int		get_dequoted_strlen(char *str);

//free.c
void	free_lexer(t_lexer *lex);
void	free_minishell(t_minishell *ms);
void	free_and_exit(t_minishell *ms);

#endif

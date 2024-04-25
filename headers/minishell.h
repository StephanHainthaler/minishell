/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:06:26 by shaintha          #+#    #+#             */
/*   Updated: 2024/04/25 11:34:05 by shaintha         ###   ########.fr       */
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


typedef enum s_type
{
	WORD = 1,
	PIPE,
	NUMBER,
	RE_IN,
	RE_OUT,
	HERE_DOC,
	APPEND,
}			t_type;

typedef struct s_simp_cmd
{
	char	**args;
	int		num_of_aval_args;
	int		num_of_args;
}			t_simp_cmd;

typedef struct s_cmd
{
	t_simp_cmd	**simp_cmds;
	int		num_of_aval_simp_cmds;
	int		num_of_simp_cmds;
	char	*infile;
	char	*outfile;
	char	*errfile;
	int		background;
}			t_cmd;

typedef struct s_lexer
{
	t_list	*token_list;
	t_type	token_type;
	char	*input;
	int		i;
}			t_lexer;	



int	read_input(void);
t_list	*lex_input(char *input);
t_list	*get_redir_token(char *input, int i);




#endif

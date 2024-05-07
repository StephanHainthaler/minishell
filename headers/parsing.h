/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:38:00 by juitz             #+#    #+#             */
/*   Updated: 2024/05/07 14:11:41 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#endif

typedef struct s_simp_cmd
{
	char	**args;
	int		num_of_aval_args;
	int		num_of_args;
}			t_simp_cmd;

typedef struct s_cmd
{
	t_simp_cmd	**simp_cmds;
	int			num_of_aval_simp_cmds;
	int			num_of_simp_cmds;
	char		*infile;
	char		*outfile;
	char		*errfile;
	int			background;
}				t_cmd;


t_simp_cmd *parse_tokens_to_struct(t_lexer *lex);
int			check_valid_input(t_lexer *lex);

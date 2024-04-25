/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/04/25 14:05:14 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	read_input(void)
{
	t_lexer	lex;
	
	lex.token_list = NULL;
	lex.input = NULL;
	lex.input = readline("./minishell ");
	if (lex.input == NULL)
		return (1);
	lex.i = 0;
	if (lex_input(&lex) == 1)
		return (1);
	ft_putlst_fd(lex.token_list, 1);
	return (0);
}

int	lex_input(t_lexer *lex)
{
	t_list	*new_token;

	while (lex->input[lex->i] != '\0')
	{
		while (ft_isspace(lex->input[lex->i]) == true)
			lex->i++;
		//if (lex->input[lex->i] == '|')			//PIPE_TOKEN		
			//get_pipe_token(lex);	//new_token = ft_lstnew("PIPE", 6);
		if (lex->input[lex->i] == '<' || lex->input[lex->i] == '>')		
			new_token = get_redir_token(lex);	//RE_DIR_TOKENS
		else
			lex->i++;
		// 	new_token = get_word_token(lex);	//WORD_TOKEN

		if (new_token == NULL)
		{
			if (lex->token_list != NULL)
				ft_lstclear(&lex->token_list);
			return (1);
		}
		ft_lstadd_back(&lex->token_list, new_token);
	}
	return (0);
}

// t_list	*get_word_token(t_lexer *lex)
// {
// 	t_list	*new_token;
// 	char	*attr;
// 	int		j;

// 	attr = NULL;
	
// }

t_list	*get_redir_token(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	t_type	type;
	int		j;

	attr = NULL;
	if (lex->input[lex->i] == '<')
		type = RE_IN;
	if (lex->input[lex->i] == '>')
		type = RE_OUT;
	lex->i++;
	if (lex->input[lex->i] == '<' && lex->input[lex->i - 1] == '<')
		type = HERE_DOC;
	if (lex->input[lex->i] == '>' && lex->input[lex->i - 1] == '>')
		type = APPEND;
	while (ft_isspace(lex->input[lex->i]) == true)
		lex->i++;
	if (lex->input[lex->i] == '\0')
		return (NULL);
	j = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (ft_isspace(lex->input[lex->i]) == true)
			break ;
		lex->i++;
		j++;
	}
	attr = (char *)malloc((j + 1) * sizeof(char));
	if (attr == NULL)
		return (NULL);
	ft_strlcpy(attr, lex->input + (lex->i - j), j);
	printf("%s\n", attr);
	printf("%c\n", lex->input[lex->i]);
	new_token = ft_lstnew(attr, type);
	return (new_token);
}

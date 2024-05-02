/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/02 12:31:19 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	read_input(t_minishell *ms)
{
	t_lexer	lex;

	lex.token_list = NULL;
	lex.input = NULL;
	lex.envp = ms->envp;
	lex.input = readline("./minishell ");
	if (lex.input == NULL)
		return (1);
	lex.i = 0;
	if (lex_input(&lex) == 1)
		return (1);
	ft_putlst_fd(lex.token_list, 1);
	// expand_env(&lex, &lex.token_list);
	// ft_putlst_fd(lex.token_list, 1);
	ft_lstclear(&lex.token_list);
	return (0);
}

int	lex_input(t_lexer *lex)
{
	t_list	*new_token;

	while (lex->input[lex->i] != '\0')
	{
		while (ft_isspace(lex->input[lex->i]) == true)
			lex->i++;
		if (lex->input[lex->i] == '\0')
			break ;
		if (is_token(lex->input[lex->i]) == true)
			new_token = get_non_word_token(lex);
		else if (lex->input[lex->i] == '\'' || lex->input[lex->i] == '\"')
			new_token = handle_quotes(lex);
		else
			new_token = get_word_token(lex);
		if (new_token == NULL)
		{
			if (lex->token_list != NULL)
				ft_lstclear(&lex->token_list);
			return (ft_putendl_fd("Error: Malloc Error", 2), 1);
		}
		ft_lstadd_back(&lex->token_list, new_token);
	}
	return (0);
}

bool	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

t_list	*get_word_token(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	int		len;

	attr = NULL;
	len = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (ft_isspace(lex->input[lex->i]) == true
			|| is_token(lex->input[lex->i]) == true)
			//|| lex->input[lex->i] == '"' || lex->input[lex->i] == '\'')
			break ;
		lex->i++;
		len++;
	}
	attr = (char *)malloc((len + 1) * sizeof(char));
	if (attr == NULL)
		return (NULL);
	ft_strlcpy(attr, lex->input + (lex->i - len), len + 1);
	new_token = ft_lstnew(WORD, attr);
	return (new_token);
}

t_list	*get_non_word_token(t_lexer *lex)
{
	t_list	*new_token;

	new_token = NULL;
	if (lex->input[lex->i] == '|')
		new_token = ft_lstnew(PIPE, NULL);
	else if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] != '<')
		new_token = ft_lstnew(RE_IN, NULL);
	else if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] != '>')
		new_token = ft_lstnew(RE_OUT, NULL);
	else if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] == '<')
	{
		new_token = ft_lstnew(HERE_DOC, NULL);
		lex->i++;
	}
	else if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] == '>')
	{
		new_token = ft_lstnew(APPEND, NULL);
		lex->i++;
	}
	lex->i++;
	return (new_token);
}

t_list	*handle_quotes(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	char	quote;
	bool	is_closed;
	int		len;

	if (lex->input[lex->i] == '\"')
		quote = '\"';
	else
		quote = '\'';
	is_closed = false;
	lex->i++;
	len = 1;
	while (lex->input[lex->i] != '\0')
	{
		if (lex->input[lex->i] == quote)
		{
			is_closed = true;
			lex->i++;
			break;
		}
		lex->i++;
		len++;
	}
	if (is_closed == false)
		return (NULL);
	attr = (char *)malloc((len + 2) * sizeof(char));
	if (attr == NULL)
		return (NULL);
	ft_strlcpy(attr, lex->input + (lex->i - 1 - len), len + 2);
	new_token = ft_lstnew(WORD, attr);
	return (new_token);
	
}

char	*handle_expansion(t_lexer *lex, char *to_expand)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	new_str = NULL;
	i = 0;
	while (to_expand[i] != '\0' && to_expand[i] != '$')
		i++;
	len = i;
	while (to_expand[len] != '\0' && ft_isspace(to_expand[len]) == false)
		len++;
	j = 0;
	while (lex->envp[j] != NULL)
	{
		//printf("%s\n", lex->envp[j]);
		if (ft_strnstr(lex->envp[j], to_expand + 1, len) == NULL)
			j++;
		else
		{
			ft_putendl_fd("HELP3", 1);
			ft_putendl_fd(lex->envp[j] + len, 1);
			ft_putnbr_fd(ft_strlen(lex->envp[j]), 1);
			ft_putstr_fd("\n", 1);
			new_str = (char *)malloc(sizeof(char) * 300);
			ft_strlcpy(new_str, lex->envp[j] + len, ft_strlen(lex->envp[j]) - ft_strlen(to_expand));
			ft_putendl_fd("HELP4", 1);
			return (new_str);
		}
	}
	return (NULL);
}

void	expand_env(t_lexer *lex, t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	if (lst == NULL)
		return ;
	while (temp != NULL)
	{
		if (ft_strchr(temp->attr, '$'))
			temp->attr = handle_expansion(lex, temp->attr);
		temp = temp->next;
	}
}

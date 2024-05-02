/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:31:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/05/02 16:31:25 by shaintha         ###   ########.fr       */
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
	//expand_env(&lex, &lex.token_list);
	check_for_expansion(&lex.token_list, ms->envp);
	ft_putendl_fd("", 1);
	ft_putlst_fd(lex.token_list, 1);
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


int	check_for_expansion(t_list **token_list, char **envp)
{
	t_list	*current_node;
	int		i;

	current_node = *token_list;
	if (token_list == NULL)
		return (1);
	while (current_node != NULL)
	{
		if (current_node->type == 1)
		{
			i = 0;
			while (current_node->attr[i] != '\0')
			{
				if (current_node->attr[i] == '$')
				{
					current_node->attr = handle_expansion(current_node->attr, envp, &i);
					continue;
				}
				i++;
			}
		}
		current_node = current_node->next;
	}
	return (0);
}

char	*handle_expansion(char *to_expand, char **envp, int *i)
{
	char	*exp_str;
	int		len;
	int		j;
	
	if (ft_isspace(to_expand[*i + 1]) == true || to_expand[*i + 1] == '\0')
		return (to_expand);
	//*i++;
	len = -1; //starts at -1 because we dont need the '$' for evnp!
	while (to_expand[len] != '\0' && ft_isspace(to_expand[len]) == false)
		len++; //len == $<env_var_name_len>
	j = 0;
	while (envp[j] != NULL)
	{
		if (ft_strnstr(envp[j], to_expand + 1, len) == NULL)
			j++;
		else
		{
			exp_str = ft_substr(envp[j], len, ft_strlen(envp[j]) - ft_strlen(to_expand) + 1);
			if (exp_str == NULL)
				return (NULL);
			*i = 0;
			return (exp_str);
		}
	}
	return (NULL);
}





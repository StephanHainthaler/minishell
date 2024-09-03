/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:44:04 by shaintha          #+#    #+#             */
/*   Updated: 2024/08/08 13:50:03 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Checks the token list for possible expansion.
//<PARAM> The token list, the environment pointers & the last exit code.
//<RETURN> 0 on SUCCESS; 1 on FATAL ERROR
int	check_for_expansion(t_list **token_list, char **envp, int ec)
{
	t_list	*cur_node;
	size_t	i;

	cur_node = *token_list;
	while (cur_node != NULL)
	{
		if (cur_node->type == WORD)
		{
			i = 0;
			while (cur_node->attr[i] != '\0')
			{
				if (cur_node->attr[i] == '\'' || cur_node->attr[i] == '"')
					handle_quotes_in_expansion(cur_node, cur_node->attr[i]);
				if (cur_node->attr[i] == '$' && cur_node->in_squotes == false)
				{
					cur_node->attr = handle_expansion(cur_node, envp, ec, &i);
					if (cur_node->attr == NULL)
						return (1);
				}
				i++;
			}
		}
		cur_node = cur_node->next;
	}
	return (0);
}

//Handles a possible expansion in the current node of the list.
//When needed, sets the position of the string accordingly.
//<PARAM> The current node, the environment pointers, 
//<PARAM> the last exit code & the position in the string.
//<RETURN> The handled string on SUCCESS; NULL on FATAL ERROR
char	*handle_expansion(t_list *node, char **envp, int exit_code, size_t *i)
{
	size_t	len;
	size_t	pos;
	size_t	j;

	if (handle_special_expansion(node, exit_code, i) == 0)
		return (node->attr);
	pos = *i;
	len = get_envname_len(node->attr, i);
	j = 0;
	while (envp[j] != NULL)
	{
		if (check_for_env(envp[j], node->attr + pos + 1, len - 1) == true)
			return (*i = pos - 1 + get_envvar_len(envp[j]),
				handle_valid_expansion(node->attr, envp[j], len, pos));
		j++;
	}
	return (*i = pos - 1, handle_invalid_expansion(node->attr, len, pos));
}

//Performs a valid expansion for the given string.
//<PARAM> The expandable string, the environment pointers, 
//<PARAM> the start of env & the position in the string.
//<RETURN> The expanded string on SUCCESS; NULL on FATAL ERROR
char	*handle_valid_expansion(char *to_expand, char *env,
			size_t len, size_t pos)
{
	char	*exp_str;
	char	*exp_var;
	size_t	i;
	size_t	j;

	exp_var = ft_substr(env, len, ft_strlen(env) - len);
	if (exp_var == NULL)
		return (NULL);
	exp_str = (char *)malloc(((ft_strlen(to_expand) \
		- len + ft_strlen(exp_var) + 1) * sizeof(char)));
	if (exp_str == NULL)
		return (free(exp_var), NULL);
	i = 0;
	j = 0;
	while (to_expand[j] != '\0' && j != pos)
		exp_str[i++] = to_expand[j++];
	j = 0;
	while (exp_var[j] != '\0')
		exp_str[i++] = exp_var[j++];
	j = pos + 1 + len - 1;
	while (to_expand[j] != '\0')
		exp_str[i++] = to_expand[j++];
	exp_str[i] = '\0';
	return (free(to_expand), free(exp_var), exp_str);
}

//Performs an invalid expansion for the given string.
//<PARAM> The expandable string, the start of env & the position in the string.
//<RETURN> The expanded string on SUCCESS; NULL on FATAL ERROR
char	*handle_invalid_expansion(char *str, size_t len, size_t pos)
{
	char	*new_str;
	size_t	i;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i != pos)
		i++;
	ft_strlcpy(new_str, str, i + 1);
	ft_strlcat(new_str + i, str + i + len, ft_strlen(str) - len - i + 1);
	free(str);
	return (new_str);
}

//Performs a valid expansion for exit codes for the given string.
//<PARAM> The expandable string, the last exit code & 
//<PARAM> the position in the string.
//<RETURN> The expanded string on SUCCESS; NULL on FATAL ERROR
char	*handle_exit_code_expansion(char *to_expand, int exit_code, size_t *i)
{
	char	*exp_str;
	char	*exp_var;
	size_t	j;
	size_t	k;
	size_t	l;

	exp_var = ft_itoa(exit_code);
	if (exp_var == NULL)
		return (NULL);
	exp_str = (char *)malloc(((ft_strlen(to_expand) - 2 + \
		ft_strlen(exp_var) + 1) * sizeof(char)));
	if (exp_str == NULL)
		return (free(exp_var), NULL);
	j = 0;
	k = 0;
	while (j != *i)
		exp_str[k++] = to_expand[j++];
	l = 0;
	while (exp_var[l] != '\0')
		exp_str[k++] = exp_var[l++];
	j = j + 2;
	while (to_expand[j] != '\0')
		exp_str[k++] = to_expand[j++];
	exp_str[k] = '\0';
	return (free(to_expand), free(exp_var), exp_str);
}

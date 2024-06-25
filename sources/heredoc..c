/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc..c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:12:06 by juitz             #+#    #+#             */
/*   Updated: 2024/06/25 16:41:46 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_heredoc(t_cmd *cmd)
{
	int i;
	
	i = cmd->cmd_nbr;
	
	while (1)
	{
		*cmd[i].heredoc = readline("heredoc>");
		if (cmd[i].heredoc == NULL)
			return ;
		if (ft_strncmp(cmd[i].delim, *cmd[i].heredoc, ft_strlen(cmd[i].delim)) != 0)
		{
			write(cmd[i].out_fd, *cmd[i].heredoc, ft_strlen(*cmd[i].heredoc));
			if (ft_strncmp(cmd[i].delim, *cmd[i].heredoc, ft_strlen(cmd[i].delim)) == 0)
				return (free(*cmd[i].heredoc));
		}
		if (ft_strncmp(cmd[i].delim, *cmd[i].heredoc, ft_strlen(cmd[i].delim)) == 0)
			break ;
	}
}

/* void	ft_heredoc(t_lexer *lex, t_list *hd_input)
{
	char	*delim;
	int		tmp_fd;
	int		tmp_fd_cpy;
	int		stdin_cpy;	
	t_list	*current;

	hd_input = NULL;
	current = lex->token_list;
	if (current->type == HERE_DOC)
	{
		current = current->next;
		delim = current->attr;
		while (1)
		{
			hd_input->tmp = readline("heredoc>");
			if (hd_input->tmp == NULL)
				return ;
			if (delim[0] == '\'' || delim[0] == '\"')
				handle_expansion(hd_input, lex->envp, 0, &lex->i);
			ft_lstadd_back(&lex->here_doc, hd_input);
			if (ft_strncmp(hd_input->tmp, delim, ft_strlen(delim)) != 0)
			{
				tmp_fd = open("temp_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
				write(tmp_fd, hd_input->tmp, ft_strlen(hd_input->tmp));
				close(tmp_fd);
				stdin_cpy = dup(STDIN_FILENO);
				tmp_fd_cpy = open("temp_file.txt", O_RDONLY);
				dup2(tmp_fd_cpy, STDIN_FILENO);
				close(tmp_fd_cpy);
				dup2(stdin_cpy, STDIN_FILENO);
				close(stdin_cpy);
				if (ft_strncmp(hd_input->tmp, delim, ft_strlen(delim)) == 0)
					return(free(lex->here_doc->tmp), free(delim));
			}
			if (ft_strncmp(hd_input->tmp, delim, ft_strlen(delim)) == 0)
					break ;
		}
	}
} */
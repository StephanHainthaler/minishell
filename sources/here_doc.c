/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by juitz             #+#    #+#             */
/*   Updated: 2024/06/27 10:50:02 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	ft_heredoc(t_cmd *cmd)
// {
// 	int i;
	
// 	i = cmd->cmd_nbr;
	
// 	while (true)
// 	{
// 		*cmd[i].heredoc = readline("> ");
// 		if (cmd[i].heredoc == NULL)
// 			return ;
// 		if (ft_strncmp(cmd[i].delim, *cmd[i].heredoc, ft_strlen(cmd[i].delim)) != 0)
// 		{
// 			write(cmd[i].out_fd, *cmd[i].heredoc, ft_strlen(*cmd[i].heredoc));
// 			if (ft_strncmp(cmd[i].delim, *cmd[i].heredoc, ft_strlen(cmd[i].delim)) == 0)
// 				return (free(*cmd[i].heredoc));
// 		}
// 		if (ft_strncmp(cmd[i].delim, *cmd[i].heredoc, ft_strlen(cmd[i].delim)) == 0)
// 			break ;
// 	}
// }

int get_here_doc_fd(char *delimiter)
{
    int     here_doc_fd;
	char	*here_doc_str;
    char    *temp;

    temp = (char *)malloc(sizeof(char));
    temp = NULL;
    printf("Test1\n");
    here_doc_fd = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0777); //read also?
    if (here_doc_fd == -1)
        return (-1);
    here_doc_str = NULL;
    printf("Test2\n");

    while (true)
	{
		temp = readline("here_doc ");
		// if (temp == NULL)
		// 	return (1);
		if (ft_isspace_str(temp) == false)
			break ;
	}
	while (true)
	{
		temp = readline("> ");
        if (temp == NULL)
            return (-1);
        printf("Test3\n");
        if (ft_isspace_str(temp) == false)
        if (strcmp(temp, delimiter) == 0)
        //if (ft_strncmp(temp, delimiter, ft_strlen(delimiter) == 0))
            break ;
        //ft_putendl_fd(temp, here_doc_fd);
        // here_doc_str = ft_strjoin_gnl(here_doc_str, temp);
        // if (here_doc_str == NULL)
        //     return (1);       
	}
    return (here_doc_fd);
}
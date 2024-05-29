/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:01:17 by juitz             #+#    #+#             */
/*   Updated: 2024/05/29 09:06:19 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_builtin(char **simp_cmd, char **envp)
{
	// if (ft_strncmp(simp_cmd[0], "echo", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (echo(), 0);
	// if (ft_strncmp(simp_cmd[0], "cd", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (cd(), 0);
	// if (ft_strncmp(simp_cmd[0], "pwd", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (pwd(), 0);
	// if (ft_strncmp(simp_cmd[0], "export", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (export(), 0);
	// if (ft_strncmp(simp_cmd[0], "unset", ft_strlen(simp_cmd[0])) == 0)
	// 	return (0); //return (unset(), 0);
	if (ft_strncmp(simp_cmd[0], "env", ft_strlen(simp_cmd[0])) == 0)
		return (ft_putstrarr_fd(envp, 1), 0);
	if (ft_strncmp(simp_cmd[0], "exit", ft_strlen(simp_cmd[0])) == 0)
		return (0);
	else
		return (1);
}

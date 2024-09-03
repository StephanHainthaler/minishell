/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:35:25 by juitz             #+#    #+#             */
/*   Updated: 2024/08/09 16:24:35 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Replicates the command echo with the option -n.
//Other options are not implemented.
//Changes the exit status depending on the outcome.
//<PARAM> The current simple command & the executor struct.
//<RETURN> void
void	ft_echo(char **simp_cmd, t_executor *exec)
{
	size_t	flag_n;
	size_t	start_index;

	start_index = parse_flag_n(simp_cmd, &flag_n);
	print_echo(simp_cmd, start_index, flag_n);
	exec->exit_status = 0;
}

//Replicates the command cd with only a relative or absolute path.
//Flags are not implemented.
//Changes the exit status depending on the outcome.
//<PARAM> The current simple command, the environment pointers &
//<PARAM> the executor struct.
//<RETURN> 0 on SUCCESS; -1 on FATAL ERROR; 2 on standard ERROR
int	ft_cd(char **simp_cmd, char **envp, t_executor *exec)
{
	char	*pwd;
	char	*oldpwd;
	int		error_check;

	if (ft_strarrlen(simp_cmd) > 2)
		return (exec->exit_status = 1,
			ft_putendl_fd("cd: too many arguments", 2), 2);
	pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (exec->exit_status = 1, -1);
	error_check = change_to_home_directory(simp_cmd, envp, exec);
	if (error_check == -1 || error_check == 2)
		return (free(oldpwd), error_check);
	error_check = change_to_other_directory(simp_cmd, envp, exec);
	if (error_check == -1 || error_check == 2)
		return (free(oldpwd), error_check);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (exec->exit_status = 1, ft_putendl_fd("cd: FATAL", 2), -1);
	envp = update_pwds(envp, pwd, oldpwd);
	if (envp == NULL)
		return (exec->exit_status = 1, ft_putendl_fd("cd: FATAL", 2), -1);
	return (exec->exit_status = 0, 0);
}

//Replicates the command pwd with no options.
//Flags are not implemented.
//Changes the exit status depending on the outcome.
//<PARAM> The executor struct.
//<RETURN> 0 on SUCCESS; -1 on FATAL ERROR
int	ft_pwd(t_executor *exec)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putendl_fd("pwd: FATAL", 2);
		return (exec->exit_status = 1, -1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (exec->exit_status = 0, 0);
}

//Replicates the command export with no options.
//Flags are not implemented.
//Changes the exit status depending on the outcome.
//<PARAM> The current simple command, the environment pointers,
//<PARAM> the executor struct & the iterator at 0.
//<RETURN> The (non-)updated environement pointers on SUCCESS;
//<RETURN> NULL on FATAL ERROR
char	**ft_export(char **simp_cmd, char **envp, t_executor *exec, size_t i)
{
	size_t	j;

	if (ft_strarrlen(simp_cmd) == 1)
	{
		if (print_declare(envp) == 1)
			return (exec->exit_status = 1, NULL);
		return (exec->exit_status = 0, envp);
	}
	exec->exit_status = 0;
	while (++i < ft_strarrlen(simp_cmd))
	{
		j = 0;
		while (envp[j] != NULL && is_replacable(envp[j], simp_cmd[i]) == false)
			j++;
		if (is_exportable(simp_cmd[i], exec, &i) == false)
			continue ;
		if (is_replacable(envp[j], simp_cmd[i]) == true)
			envp = ft_strreplace_instrarr(envp, simp_cmd[i], j);
		else
			envp = ft_stradd_tostrarr(envp, simp_cmd[i]);
		if (envp == NULL)
			return (exec->exit_status = 1,
				ft_putendl_fd("export: FATAL", 2), NULL);
	}
	return (envp);
}

//Replicates the command unset with no options.
//Flags are not implemented.
//Changes the exit status depending on the outcome.
//<PARAM> The current simple command, the environment pointers &
//<PARAM> the executor struct & the iterator at 1.
//<RETURN> The (non-)updated environement pointers on SUCCESS;
//<RETURN> NULL on FATAL ERROR
char	**ft_unset(char **simp_cmd, char **envp, t_executor *exec, size_t i)
{
	size_t	pos;

	if (ft_strarrlen(simp_cmd) == 1)
		return (exec->exit_status = 0, envp);
	while (i < ft_strarrlen(simp_cmd))
	{
		pos = 0;
		while (envp[pos] != NULL)
		{
			if (check_for_env(envp[pos], simp_cmd[i], \
				ft_strlen(simp_cmd[i])) == false)
			{
				pos++ ;
				continue ;
			}
			envp = ft_strdel_fromstrarr(envp, pos);
			if (envp == NULL)
				return (exec->exit_status = 1,
					ft_putendl_fd("unset: FATAL", 2), NULL);
			break ;
		}
		i++;
	}
	return (exec->exit_status = 0, envp);
}

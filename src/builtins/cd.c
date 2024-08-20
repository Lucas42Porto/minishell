/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:23:38 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 19:38:06 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*path;
	char	*newpwd;
	char	*tmp;
	
	path = NULL;
	if (cmd->argv[1])
		path = cmd->argv[1];
	if (cmd->argv[2])
		print_error(shell, "cd", "too many arguments", 1);
	else
	{
		tmp = getcwd(NULL, 0);
		if (!path)
			path = env_get(&shell->env, "HOME");
		else if (!ft_strcmp(path, "-"))
		{
			path = shell->oldpwd;
			if (!shell->oldpwd)
				print_error(shell, "cd", "OLDPWD not defined", 2);
			else
				ft_putendl_fd(shell->oldpwd, STDOUT_FILENO);
		}
		if (!chdir(path) && shell->status == CONTINUE)
		{
			shell->oldpwd = ft_strdup(tmp);
			update_env(&shell->env, "OLDPWD", shell->oldpwd);
			newpwd = getcwd(NULL, 0);
			update_env(&shell->env, "PWD", newpwd);
			free(newpwd);
		}
		else if (shell->status == CONTINUE)
			print_error(shell, "cd: No such file or directory", path, 1);
		free(tmp);
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}

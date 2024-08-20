/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:23:38 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:06:17 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_cd(t_shell *shell, t_exec *cmd, char *path)
{
	char	*newpwd;
	char	*tmp;

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
		print_error(shell, "cd: No such file or directory", path, 2);
	free(tmp);
}

void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->argv[1])
		path = cmd->argv[1];
	if (cmd->argv[2])
		print_error(shell, "cd", "too many arguments", 2);
	else
		ft_cd(shell, cmd, path);
	if (shell->status == CONTINUE)
		g_exit = 0;
}

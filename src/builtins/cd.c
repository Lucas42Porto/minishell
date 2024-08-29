/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:23:38 by resilva           #+#    #+#             */
/*   Updated: 2024/08/29 19:04:53 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ex_cd(t_shell *shell, char *path, char *tmp)
{
	char	*newpwd;

	if (shell->status == CONTINUE && (!path || !ft_strcmp(path, "~")))
		path = env_get(&shell->env, "HOME");
	else if (!ft_strcmp(path, "-"))
	{
		path = shell->oldpwd;
		if (!shell->oldpwd)
			print_error(shell, "cd", "OLDPWD not defined", 1);
		else
			ft_putendl_fd(shell->oldpwd, STDOUT_FILENO);
	}
	if (!chdir(path) && shell->status == CONTINUE)
	{
		if (shell->oldpwd)
			free(shell->oldpwd);
		shell->oldpwd = ft_strdup(tmp);
		update_env(&shell->env, "OLDPWD", shell->oldpwd);
		newpwd = getcwd(NULL, 0);
		update_env(&shell->env, "PWD", newpwd);
		free(newpwd);
	}
	else if (shell->status == CONTINUE)
		print_error(shell, "cd: No such file or directory", path, 1);
}

static char	*prepare_cd(t_shell *shell, t_exec *cmd)
{
	char	*path;
	int		args;
	int		i;

	path = NULL;
	args = 0;
	i = 1;
	while (i < (MAXARGS - 1))
		if (shell->argv_index[i++] == 1)
			args++;
	i = 1;
	while (shell->argv_index[i] == 0 && i < (MAXARGS - 1))
		i++;
	if (cmd->argv[i])
		path = cmd->argv[i];
	if (args > 1)
		print_error(shell, "cd", "too many arguments", 1);
	else if (!env_get(&shell->env, "HOME"))
		print_error(shell, "cd", "HOME not set", 1);
	return (path);
}

void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*path;
	char	*tmp;
	int		flag;

	tmp = getcwd(NULL, 0);
	flag = 0;
	if (tmp)
		flag = 1;
	else
		tmp = env_get(&shell->env, "PWD");
	path = prepare_cd(shell, cmd);
	if (shell->status == CONTINUE)
		ex_cd(shell, path, tmp);
	if (flag)
		free(tmp);
	if (shell->status == CONTINUE)
		g_exit = 0;
}

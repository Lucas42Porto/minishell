/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:10:49 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 21:13:29 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
		perror("fork");
		g_exit = 127;
	}
	return (pid);
}

void	check(int result, char *msg, int exit)
{
	if (result == -1)
	{
		ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
		perror(msg);
		g_exit = exit;
	}
}

int	run_builtin(t_shell *shell, t_exec *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ms_echo(cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ms_cd(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ms_pwd(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (ms_export(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ms_unset(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (ms_env(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ms_exit(shell, cmd), 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:23:38 by resilva           #+#    #+#             */
/*   Updated: 2024/08/14 22:30:55 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*path;
	
	path = NULL;
	if (cmd->argv[1])
		path = cmd->argv[1];
	if (cmd->argv[2])
		print_error(shell, "cd", "too many arguments", 2);
	else
	{
		if (!path)
			path = getenv("HOME");
		// else if (!ft_strcmp(path, "~") || !ft_strcmp(path, "~/"))
		// 	path = getenv("HOME");
		else if (!ft_strcmp(path, "-"))
		{
			path = getenv("OLDPWD");
			if (!path)
				print_error(shell, "cd", "OLDPWD not defined", 2);
		}
		if (chdir(path))
			print_error(shell, "cd: No such file or directory", path, 2);
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}

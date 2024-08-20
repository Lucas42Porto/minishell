/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:10:02 by resilva           #+#    #+#             */
/*   Updated: 2024/08/19 22:07:14 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env(t_shell *sh, int i)
{
	while (++i < sh->env.size_env)
	{
		if (sh->env.e_content[i])
		{
			ft_putstr_fd(sh->env.e_name[i], STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(sh->env.e_content[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);	
		}
	}
}

void	ms_env(t_shell *shell, t_exec *cmd)
{
	if (cmd->argv[1])
		print_error(shell, "env", "Arguments and options are not supported", 2);
	else
	{
		if (env_get(&shell->env, "PATH"))
			print_env(shell, -1);
		else
			print_error(shell, "env", "No such file or directory", 127);
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}


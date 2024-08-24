/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:03:58 by resilva           #+#    #+#             */
/*   Updated: 2024/08/24 20:54:58 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_pwd(t_shell *sh, t_exec *cmd)
{
	char	path[1024];
	char	*tmp;

	if (cmd->argv[1] && *cmd->argv[1] == '-')
	{
		print_error(sh, ERROR_OPT, NULL, 2);
		return ;
	}
	if (getcwd(path, sizeof(path)))
		ft_putendl_fd(path, STDOUT_FILENO);
	else
	{
		if (!env_get(&sh->env, "PWD"))
			print_error(sh, "Unable to get current directory", NULL, 2);
		else
		{
			tmp = env_get(&sh->env, "PWD");
			ft_putendl_fd(tmp, STDOUT_FILENO);
		}
	}
	if (sh->status == CONTINUE)
		g_exit = 0;
}

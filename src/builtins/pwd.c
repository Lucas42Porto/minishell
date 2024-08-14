/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:03:58 by resilva           #+#    #+#             */
/*   Updated: 2024/08/14 18:04:13 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_pwd(t_shell *sh, t_exec *cmd)
{
	char	path[1024];

	if (cmd->argv[1] && *cmd->argv[1] == '-')
	{
		print_error(sh, ERROR_OPT, NULL, 2);
		return ;	
	}
	if (getcwd(path, sizeof(path)))
		ft_putendl_fd(path, STDOUT_FILENO);
	else
		print_error(sh, "Unable to get current directory", NULL, 2);
}

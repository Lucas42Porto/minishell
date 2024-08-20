/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:44:46 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:08:19 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_exit(t_exec *cmd)
{
	int	i;

	i = -1;
	while (cmd->argv[1][++i])
	{
		if (i == 0 && (cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+'))
			i++;
		if (!ft_isdigit(cmd->argv[1][i]))
			return (FALSE);
	}
	g_exit = ft_atoi(cmd->argv[1]);
	return (TRUE);
}

void	ms_exit(t_shell *shell, t_exec *cmd)
{
	char	*err;

	err = NULL;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->argv[2])
		print_error(shell, "exit", "too many arguments", 2);
	else if (cmd->argv[1])
	{
		if (!valid_exit(cmd))
		{
			err = ft_strjoin(cmd->argv[1], ": numeric argument required");
			print_error(shell, "exit", err, 2);
			free(err);
		}
	}
	clean_exit(shell);
}

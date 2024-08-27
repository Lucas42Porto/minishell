/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:44:46 by resilva           #+#    #+#             */
/*   Updated: 2024/08/27 22:34:50 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_exit(char *str, int i)
{
	int	negative;
	int	len;
	int	sign;

	negative = 0;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
		sign = 1;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (FALSE);
	}
	len = ft_strlen(str) - sign;
	if (len > 19)
		return (FALSE);
	if (negative)
		return (ft_strncmp(str + sign, "9223372036854775808", len) <= 0);
	else
		return (ft_strncmp(str + sign, "9223372036854775807", len) <= 0);
}

static void	many_args(t_shell *shell, t_exec *cmd)
{
	char	*err;

	err = NULL;
	if (!ft_isdigit(cmd->argv[1][0]))
	{
		err = ft_strjoin(cmd->argv[1], ": numeric argument required");
		print_error(shell, "exit", err, 2);
		free(err);
	}
	else
		print_error(shell, "exit", "too many arguments", 1);
}

void	ms_exit(t_shell *shell, t_exec *cmd)
{
	char	*err;
	int		flag_exit;

	err = NULL;
	flag_exit = 0;
	if (shell->flag_pipe != 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->argv[2])
	{
		flag_exit = 1;
		many_args(shell, cmd);
	}
	else if (cmd->argv[1])
	{
		if (!valid_exit(cmd->argv[1], 0))
		{
			err = ft_strjoin(cmd->argv[1], ": numeric argument required");
			print_error(shell, "exit", err, 2);
			free(err);
		}
	}
	if (shell->status == CONTINUE && cmd->argv[1])
		g_exit = ft_atoi(cmd->argv[1]);
	if (!flag_exit || !ft_isdigit(cmd->argv[1][0]))
		clean_exit(shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:44:46 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 21:07:53 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_exit(char *str)
{
	int	i;
	int	negative;
	int	len;

	i = 0;
	negative = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
		str++;
	}
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (FALSE);
	len = ft_strlen(str);
	if (len > 19)
		return (FALSE);
	if (negative)
		return (ft_strncmp(str + 1, "9223372036854775808", len) <= 0);
	else
		return (ft_strncmp(str, "9223372036854775807", len) <= 0);
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
		if (!valid_exit(cmd->argv[1]))
		{
			err = ft_strjoin(cmd->argv[1], ": numeric argument required");
 			print_error(shell, "exit", err, 2);
			free(err);
		}
	}
	if (shell->status == CONTINUE)
		g_exit = ft_atoi(cmd->argv[1]);
	clean_exit(shell);
}

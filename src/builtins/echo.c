/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:36 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:06:44 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_flag(char **argv, int *i)
{
	int	j;
	int	flag;

	flag = FALSE;
	while (argv[*i] && !ft_strncmp(argv[*i], "-n", 2))
	{
		j = 2;
		while (argv[*i][j] == 'n')
		{
			j++;
			if (argv[*i][j] && argv[*i][j] != 'n')
				return (flag);
		}
		flag = TRUE;
		(*i)++;
	}
	return (flag);
}

void	ms_echo(t_exec *cmd)
{
	int	i;
	int	break_l;

	i = 1;
	break_l = check_flag(cmd->argv, &i);
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i++], STDOUT_FILENO);
		if (cmd->argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!break_l)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit = 0;
}

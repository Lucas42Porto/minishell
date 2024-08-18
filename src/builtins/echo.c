/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:36 by resilva           #+#    #+#             */
/*   Updated: 2024/08/15 06:01:42 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int	check_flag(char **argv, int *i)
// {
// 	int	j;
// 	int flag;
	
// 	flag = FALSE;
// 	while (argv[*i] && !ft_strncmp(argv[*i], "-n", 2))
// 	{
// 		j = 2;
// 		while (argv[*i][j] == 'n')
// 		{
// 			j++;
// 			if (argv[*i][j] && argv[*i][j] != 'n')
// 				return (flag);
// 		}
// 		flag = TRUE;
// 		(*i)++;
// 	}
// 	return (flag);
// }

// void	ms_echo(t_exec *cmd)
// {
// 	int	i;
// 	int	break_l;

// 	i = 1;
// 	break_l = check_flag(cmd->argv, &i);
// 	while (cmd->argv[i])
// 	{
// 		ft_putstr_fd(cmd->argv[i++], STDOUT_FILENO);
// 		if (cmd->argv[i])
// 			ft_putchar_fd(' ', STDOUT_FILENO);
// 	}
// 	if (!break_l)
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	g_exit = 0;
// }

static int	ft_contains_only(char *str, char *characters)
{
	while (*str)
	{
		if (!ft_strchr(characters, *str++))
			return (0);
	}
	return (1);
}

static int	echo_flag(t_exec *cmd, int *arg_index)
{
	int	flag;

	flag = 0;
	while (cmd->argv[++*arg_index])
	{
		if (cmd->argv[*arg_index][0] == '-')
		{
			if (ft_contains_only(&cmd->argv[*arg_index][1], "n"))
				flag = 1;
			else
				break ;
		}
		else
			break ;
	}
	return (flag);
}

void	ms_echo(t_exec *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = echo_flag(cmd, &i);
	if (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		while (cmd->argv[++i])
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit = 0;
}

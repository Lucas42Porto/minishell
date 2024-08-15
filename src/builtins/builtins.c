/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:58:35 by resilva           #+#    #+#             */
/*   Updated: 2024/08/14 22:26:28 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_exit(t_shell *shell, char *cmd, char *arg, int ntokens)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd);
	if (len_cmd == 4)
	{
		if (ntokens > 2)
			printf("too many arguments");
		// ft_error(cmd, NULL, "too many arguments");
		else
			clean_exit(shell, arg);
	}
	else
		printf("command not found");
	//ft_error(cmd, NULL, "command not found");
}

// void	ft_exec_cmd(t_shell *shell, char *line)
// {
// 	char	**cmd_args;
// 	char	*arg1;
// 	char	*cmd;
// 	int		ntokens;

// 	cmd_args = ft_split(line, ' ');
// 	cmd = ft_strdup(cmd_args[0]);
// 	arg1 = NULL;
// 	if (cmd_args[1])
// 		arg1 = ft_strdup(cmd_args[1]);
// 	ntokens = ft_count_tokens(cmd_args);
// 	if (ft_strncmp(cmd, "cd", 2) == 0)
// 		ft_exec_cd(cmd, arg1, ntokens);
// 	else if (ft_strncmp(cmd, "pwd", 3) == 0)
// 		ft_exec_pwd(cmd);
// 	else if (ft_strncmp(cmd, "echo", 4) == 0)
// 		ft_exec_echo(cmd_args, cmd, ntokens, ft_strlen(cmd));
// 	else if (!ft_strncmp(cmd, "env", 3))
// 		ft_exec_env(shell, cmd, ft_strlen(cmd), -1);
// 	else if (!ft_strncmp(cmd, "exit", 4))
// 		ft_exec_exit(shell, cmd, arg1, ntokens);
// 	free_split(cmd_args);
// 	free(cmd);
// 	free(arg1);
// }

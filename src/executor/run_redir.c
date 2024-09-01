/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:37:07 by lumarque          #+#    #+#             */
/*   Updated: 2024/09/01 23:38:07 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	expand_file(t_shell *shell, char **file)
{
	int	len;

	expand_arg(shell, file);
	len = ft_strlen(*file);
	arg_insert_null(*file);
	trim_quotes(shell, *file, &len);
	return (1);
}

void	run_redir(t_shell *shell, t_redir *cmd)
{
	int	fd;
	int	original_fd;

	shell->flag_redir = 1;
	original_fd = dup(cmd->fd);
	fd = -2;
	if (expand_file(shell, &cmd->file))
		fd = open(cmd->file, cmd->mode, 0644);
	if (fd == -1)
		print_error(shell, cmd->file, strerror(errno), 1);
	else if (shell->status == CONTINUE)
	{
		dup2(fd, cmd->fd);
		close(fd);
		run_cmd(shell, cmd->cmd);
	}
	check(dup2(original_fd, cmd->fd), "dup2 error", 1);
	shell->flag_redir = 0;
}

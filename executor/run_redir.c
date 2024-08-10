/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:37:07 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/09 00:20:07 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check(int result, char *msg, int exit)
{
	if (result == -1)
	{
		ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
		perror(msg);
		g_exit = exit;
	}
}

static int	expand_file(t_shell *shell, char **file)
{
	int	len;

	expand_arg(shell, file); //expande o tilde e as variáveis de ambiente.
	len = ft_strlen(*file);
	arg_insert_null(*file); //inserir um caractere nulo em cada espaço em branco que não está entre aspas
	trim_quotes(*file, &len); //remover as aspas do arquivo de redirecionamento.
	return (1);
}

void	run_redir(t_shell *shell, t_redir *cmd)
{
	int	fd;
	int	original_fd;

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
}
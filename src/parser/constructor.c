/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:24:35 by resilva           #+#    #+#             */
/*   Updated: 2024/08/24 17:31:04 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*mk_here(char *eof, t_cmd *cmd)
{
	t_here	*here;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HEREDOC;
	here->eof = ft_strdup(eof);
	here->fdin = dup(STDIN_FILENO);
	here->fdout = dup(STDOUT_FILENO);
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->type == EXEC || cmd->type == REDIR || cmd->type == HEREDOC)
		here->cmd = cmd;
	else
	{
		tmp = cmd;
		while (tmp->type != EXEC && tmp->type != REDIR)
		{
			tmp2 = tmp;
			tmp = ((t_redir *)tmp)->cmd;
		}
		((t_redir *)tmp2)->cmd = (t_cmd *)here;
		here->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)here);
}

t_cmd	*mk_pipe(t_cmd *left, t_cmd *right)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}

t_redir	*init_rd(char *file, int mode, int fd, t_cmd *cmd)
{
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	redir->file = ft_strdup(file);
	redir->type = REDIR;
	redir->mode = mode;
	redir->fd = fd;
	if (cmd->type == EXEC || cmd->type == HEREDOC)
		redir->cmd = cmd;
	return (redir);
}

t_cmd	*mk_redir(char *file, int mode, int fd, t_cmd *cmd)
{
	t_redir	*redir;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	redir = init_rd(file, mode, fd, cmd);
	if (!(cmd->type == EXEC || cmd->type == HEREDOC))
	{
		tmp = cmd;
		while (tmp->type != EXEC)
		{
			tmp2 = tmp;
			if (tmp->type == REDIR)
				tmp = ((t_redir *)tmp)->cmd;
			else
				tmp = ((t_here *)tmp)->cmd;
		}
		if (tmp2->type == REDIR)
			((t_redir *)tmp2)->cmd = (t_cmd *)redir;
		else
			((t_here *)tmp2)->cmd = (t_cmd *)redir;
		redir->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)redir);
}

t_cmd	*mk_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	exec->type = EXEC;
	return ((t_cmd *)(exec));
}

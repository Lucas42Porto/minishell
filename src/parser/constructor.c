/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:24:35 by resilva           #+#    #+#             */
/*   Updated: 2024/08/10 00:50:48 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*mk_here(char *eof, t_cmd *subcmd)
{
	t_here	*here;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HEREDOC;
	here->eof = ft_strdup(eof);
	here->fdin = dup(STDIN_FILENO);
	here->fdout = dup(STDOUT_FILENO);
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	here->cmd = subcmd;
	return ((t_cmd *)here);
}

t_cmd	*mk_pipe(t_cmd *left, t_cmd *right) //make pipe
{
	t_pipe	*pipe;

	pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}

t_cmd	*mk_redir(char *file, int mode, int fd, t_cmd *subcmd)
{
	t_redir	*redir;
	
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	redir->file = ft_strdup(file);
	redir->type = REDIR;
	redir->mode = mode;
	redir->fd = fd;
	redir->cmd = subcmd;
	
	return ((t_cmd *)redir);
}

t_cmd	*mk_exec(void)
{
	t_exec	*exec;
	
	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	exec->type = EXEC;
	return ((t_cmd *)(exec));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:11:45 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:12:22 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->argv[0])
		free(exec->argv[0]);
	free(exec);
	exec = NULL;
}

static void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free_cmd(redir->cmd);
	if (redir->file)
		free(redir->file);
	free(redir);
	redir = NULL;
}

static void	free_here(t_here *here)
{
	if (!here)
		return ;
	free_cmd(here->cmd);
	if (here->eof)
		free(here->eof);
	free(here);
	here = NULL;
}

static void	free_pipe(t_pipe *pipe)
{
	if (!pipe)
		return ;
	free_cmd(pipe->left);
	free_cmd(pipe->right);
	free(pipe);
	pipe = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	else if (cmd->type == PIPE)
		free_pipe((t_pipe *)cmd);
	else if (cmd->type == HEREDOC)
		free_here((t_here *)cmd);
	else if (cmd->type == REDIR)
		free_redir((t_redir *)cmd);
	else if (cmd->type == EXEC)
		free_exec((t_exec *)cmd);
}
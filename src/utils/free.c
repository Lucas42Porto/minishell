/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:31:28 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 16:18:29 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_exec(t_exec *exec)
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

void	clean_exit(t_shell *shell)
{
	if (shell->paths)
		free_split(shell->paths);
	free_split(shell->env.e_name);
	free_split(shell->env.e_content);
	free(shell->user_line);
	if (shell->oldpwd)
		free(shell->oldpwd);
	exit(g_exit);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		if (split[i])
			free(split[i]);
	free(split);
}

void	free_exit(t_shell *shell)
{
	if (shell->user_line)
		free(shell->user_line);
	free_cmd(shell->cmd);
	exit(g_exit);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:57:22 by resilva           #+#    #+#             */
/*   Updated: 2024/08/28 00:09:58 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_here	*init_here(char *eof, t_cmd *cmd)
{
	t_here	*here;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HEREDOC;
	here->eof = ft_strdup(eof);
	here->fdin = dup(STDIN_FILENO);
	here->fdout = dup(STDOUT_FILENO);
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->type == EXEC || cmd->type == REDIR)
		here->cmd = cmd;
	return (here);
}

t_cmd	*mk_here(char *eof, t_cmd *cmd)
{
	t_here	*here;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	here = init_here(eof, cmd);
	if ((cmd->type != EXEC && cmd->type != REDIR))
	{
		tmp = cmd;
		while (tmp->type != EXEC && tmp->type != REDIR)
		{
			tmp2 = tmp;
			if (tmp->type == REDIR)
				tmp = ((t_redir *)tmp)->cmd;
			else
				tmp = ((t_here *)tmp)->cmd;
		}
		if (tmp2->type == REDIR)
			((t_redir *)tmp2)->cmd = (t_cmd *)here;
		else
			((t_here *)tmp2)->cmd = (t_cmd *)here;
		here->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)here);
}

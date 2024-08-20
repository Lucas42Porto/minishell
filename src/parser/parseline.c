/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:52:36 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:59:07 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*parseredir(t_shell *sh, t_cmd *cmd)
{
	char	*token;
	int		type;

	while (peek(sh, "<>"))
	{
		type = gettoken(sh, NULL);
		if (gettoken(sh, &token) != 'a')
			return (print_error_syntax(sh, token, 2), cmd);
		if (type == '<')
			cmd = mk_redir(token, O_RDONLY, 0, cmd);
		else if (type == '>')
			cmd = mk_redir(token, O_WRONLY | O_CREAT | O_TRUNC, 1, cmd);
		else if (type == APPEND)
			cmd = mk_redir(token, O_WRONLY | O_CREAT | O_APPEND, 1, cmd);
		else if (type == HEREDOC)
			cmd = mk_here(token, cmd);
	}
	return (cmd);
}

t_cmd	*parseexec(t_shell *sh)
{
	t_exec	*cmd;
	t_cmd	*ret;
	char	*token;
	int		type;

	ret = mk_exec();
	cmd = (t_exec *)ret;
	ret = parseredir(sh, ret);
	while (!peek(sh, "|"))
	{
		type = gettoken(sh, &token);
		if (!type)
			break ;
		if (type != 'a')
			return (print_error_syntax(sh, token, 2), ret);
		if (cmd->argv[0])
			cmd->argv[0] = ft_strjoin_free_s1(cmd->argv[0], " ");
		cmd->argv[0] = ft_strjoin_free_s1(cmd->argv[0], token);
		ret = parseredir(sh, ret);
	}
	return (ret);
}

t_cmd	*parsepipe(t_shell *sh)
{
	t_cmd	*cmd;

	cmd = parseexec(sh);
	if (cmd && peek(sh, "|"))
	{
		gettoken(sh, NULL);
		cmd = mk_pipe(cmd, parsepipe(sh));
	}
	return ((t_cmd *)cmd);
}

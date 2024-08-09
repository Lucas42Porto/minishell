/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:52:36 by resilva           #+#    #+#             */
/*   Updated: 2024/08/09 01:54:33 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*c;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	c = (char *) malloc(len * sizeof(char) + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		c[i + j] = s2[j];
		j++;
	}
	c[i + j] = '\0';
	if (s1)
		free(s1);
	return (c);
}

t_cmd	*parseredir(t_shell *sh, t_cmd *cmd)
{
	char	*token;
	int		type;

	while (peek(sh, "<>"))
	{
		type = gettoken(sh, NULL);
		if (gettoken(sh, &token) != 'a')
			return (ft_error("minishell", NULL, "syntax"), NULL);
		if (type == '<')
			cmd = mk_redir(token, O_RDONLY, 0, cmd);
		else if (type == '>')
			cmd = mk_redir(token, O_WRONLY | O_CREAT | O_TRUNC, 1, cmd);
		else if (type == APPEND)
			cmd = mk_redir(token, O_WRONLY | O_CREAT | O_APPEND, 1, cmd);
		// else if (type == HEREDOC)
		// 	cmd = mk_here()
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
			break;
		if (type != 'a')
			return (ft_error("minishell", NULL, "syntax"), NULL);
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
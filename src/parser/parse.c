/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:45:25 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:58:07 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	gettoken_type(t_shell *sh)
{
	int	type;

	type = *sh->ps;
	if (*sh->ps == '<')
	{
		if (*(sh->ps + 1) == '<')
			type = HEREDOC;
	}
	else if (*sh->ps == '>')
	{
		if (*(sh->ps + 1) == '>')
			type = APPEND;
	}
	else if (*sh->ps && !ft_strchr(OPERATORS, *sh->ps))
		type = 'a';
	if (*sh->ps && type != 'a')
		sh->ps += (type == HEREDOC || type == APPEND) + 1;
	return (type);
}

int	gettoken(t_shell *sh, char **token)
{
	int	type;

	while (sh->ps < sh->es && !*sh->ps)
		sh->ps++;
	if (token)
		*token = sh->ps;
	type = gettoken_type(sh);
	while (type == 'a' && sh->ps < sh->es && *sh->ps)
		sh->ps++;
	while (sh->ps < sh->es && !*sh->ps)
		sh->ps++;
	return (type);
}

int	peek(t_shell *sh, char *tok)
{
	while (sh->ps < sh->es && !*sh->ps)
		sh->ps++;
	return (sh->ps < sh->es && ft_strchr(tok, *sh->ps));
}

int	parse(t_shell *sh)
{
	sh->ps = sh->user_line;
	sh->es = sh->user_line + sh->size_line;
	sh->cmd = parsepipe(sh);
	peek(sh, "");
	if (sh->ps != sh->es && sh->status != RESTORE)
		return (!print_error_syntax(sh, sh->ps, 2));
	return (sh->status == CONTINUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:44:32 by resilva           #+#    #+#             */
/*   Updated: 2024/08/07 02:16:31 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	wrong_pipe(char *user_line, int size_line)
// {
// 	if (user_line[0] == '|' || user_line[size_line - 1] == '|')
// 		return (ft_error("Syntax error", NULL, "\"|\" unexpected"), 1);
// 	return (0);
// }

// int	wrong_redir(char *user_line, int i)
// {
// 	if (user_line[])
// 	while (user_line[++i])
// 	{
// 		if (user_line[i] == '|' && user_line[i - 1] == '>')
// 	}
// }

int	wrong_pipe(char *line, int i, int j) // i=-1 & j=0
{
	int	consecutive_pipes;

	consecutive_pipes = 0;
	if (*line == '|')
		return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), TRUE);
	while (line[++i])
	{
		if (line[i] == '|')
		{
			while (line[i + (++j)] == '|')
				if ((consecutive_pipes++) >= 3)
					return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
					
			if (consecutive_pipes == 1) // (consecutive_pipes == 1 || consecutive_pipes >= 3)
				return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
			else if (consecutive_pipes == 2)
				return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), TRUE);
		}
	}
	return (FALSE);
}

int	wrong_quote(char *line, int squote, int dquote, int i)
{
	while (line[++i])
	{
		if (line[i] == '"' && !squote)
			dquote = !dquote;
		else if (line[i] == '\'' && !dquote)
			squote = !squote;
	}
	if (squote || dquote)
		return (TRUE);
	return (FALSE);
}

int	lexer(t_shell *shell)
{
	char	last_char;

	last_char = shell->user_line[shell->size_line - 1];
	if (*shell->user_line == '|')
		return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), FALSE);
	else if (wrong_quote(shell->user_line, 0, 0, -1))
		return (ft_error("minishell", NULL, ERROR_QUOTES), FALSE);
	else if (last_char == '|')
		return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), FALSE);
	else if(ft_strchr("<>", last_char))
		return (ft_error("minishell", NULL, "syntax error near unexpected token `newline'"), FALSE);
	return (TRUE);
}
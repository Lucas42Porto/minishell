/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:44:32 by resilva           #+#    #+#             */
/*   Updated: 2024/08/09 03:44:24 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

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

int	wrong_pipe(char *line, int i) // i=-1 & j=0
{
	// int	consecutive_pipes;

	// consecutive_pipes = 0;
	// if (*line == '|')
	// {
	// 	if (*line + 1 == '|')
	// 		return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
	// 	return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), TRUE);
	// }
	// while (line[++i])
	// {
	// 	if (line[i] == '|')
	// 	{
	// 		while (line[i + (++j)] == '|')
	// 			if ((consecutive_pipes++) >= 3)
	// 				return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
					
	// 		if (consecutive_pipes == 1) // (consecutive_pipes == 1 || consecutive_pipes >= 3)
	// 			return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
	// 		else if (consecutive_pipes == 2)
	// 			return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), TRUE);
	// 	}
	// }

	while (line[++i])
	{
		// if (line[i] == '"' || line == '\'')
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
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

void	nullterminate(t_shell *sh, int i)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (sh->user_line[++i])
	{
		if (sh->user_line[i] == '\'' && !dquote)
			squote = !squote;
		else if (sh->user_line[i] == '"' && !squote)
			dquote = !dquote;
		if (!squote && !dquote && ft_strchr(SPACES, sh->user_line[i]))
			sh->user_line[i] = '\0';
	}
}

int	expand(t_shell *shell, char *line, int i)
{
	char	*newline;
	char	*left;
	char	*right;
	
	newline = ft_substr(line, 0, i);
	left = ft_strjoin(newline, " ");
	free(newline);
	right = ft_substr(line, i, ft_strlen(line) - i);
	newline = ft_strjoin(left, right);
	free(shell->user_line);
	shell->user_line = ft_strdup(newline);
	free(newline);
	free(left);
	free(right);
	return (TRUE);
}

void	check_expand(t_shell *shell, char *line)
{
	int		squote;
	int		dquote;

	squote = 0;
	dquote = 0;
	while (*line)
	{
		if (*line == '"' && !squote)
			dquote = !dquote;
		else if (*line == '\'' && !dquote)
			squote = !squote;
		if (!squote && !dquote && (ft_strchr("|<>", *line)))
		{
			if (!ft_strchr(" |<>", *(line - 1)))
			{
				if (expand(shell, shell->user_line, line - shell->user_line))
					line = shell->user_line;
			}
			else if (!ft_strchr(" |<>", *(line + 1)))
				if (expand(shell, shell->user_line, line - shell->user_line + 1))
					line = shell->user_line;
		}
		line++;
	}
	shell->size_line = ft_strlen(shell->user_line);
}

int	lexer(t_shell *shell)
{
	//char	last_char;

	// last_char = shell->user_line[shell->size_line - 1];
	// if (*shell->user_line == '|')
	// 	return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), FALSE);
	// else if (wrong_quote(shell->user_line, 0, 0, -1))
	// 	return (ft_error("minishell", NULL, ERROR_QUOTES), FALSE);
	// else if (last_char == '|')
	// 	return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), FALSE);
	// else if(ft_strchr("<>", last_char))
	// 	return (ft_error("minishell", NULL, "syntax error near unexpected token `newline'"), FALSE);

	check_expand(shell, shell->user_line);
	nullterminate(shell, -1);
	return (TRUE);
}
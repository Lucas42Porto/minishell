/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:44:32 by resilva           #+#    #+#             */
/*   Updated: 2024/08/10 14:38:52 by resilva          ###   ########.fr       */
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

int	wrong_pipe(char *line, int i) // i=-1 & j=0
{
	(void)line;
	(void)i;
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


	// while (line[++i])
	// {
	// 	// if (line[i] == '"' || line == '\'')
	// 	if (line[i] == '|')
	// 	{
	// 		if (line[i + 1] == '|')
	// 			return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE2), TRUE);
	// 		return (ft_error("minishell", NULL, ERROR_SYNTAX_PIPE), TRUE);
	// 	}
	// }

	return (FALSE);
}

int	wrong_quote(t_shell *sh, char *line, int squote, int dquote)
{
	while (*line)
	{
		if (*line == '"' && !squote)
			dquote = !dquote;
		else if (*line == '\'' && !dquote)
			squote = !squote;
		line++;
	}
	if (squote || dquote)
		return (print_error(sh, ERROR_QUOTE, NULL, 2));
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

int	expand_parse(t_shell *shell, char *line, int i)
{
	char	*new_line;
	char	*left;
	char	*right;
	
	new_line = ft_substr(line, 0, i);
	left = ft_strjoin(new_line, " ");
	free(new_line);
	right = ft_substr(line, i, ft_strlen(line) - i);
	new_line = ft_strjoin(left, right);
	free(shell->user_line);
	shell->user_line = ft_strdup(new_line);
	free(new_line);
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
		if (!squote && !dquote && (ft_strchr("<|>", *line)))
		{
			if (!ft_strchr(" |<>", *(line - 1)))
			{
				if (expand_parse(shell, shell->user_line, line - shell->user_line))
					line = shell->user_line;
			}
			else if (!ft_strchr(" |<>", *(line + 1)))
				if (expand_parse(shell, shell->user_line, line - shell->user_line + 1))
					line = shell->user_line;
		}
		line++;
	}
	shell->size_line = ft_strlen(shell->user_line);
}

int	syntax_error(t_shell *sh)
{
	char	last_char;
	
	last_char = sh->user_line[ft_strlen(sh->user_line) - 1];
	if (ft_strchr(BAD_OP, *sh->user_line))
		return (!print_error_syntax(sh, *sh->user_line, 2));
	else if (wrong_quote(sh, sh->user_line, 0, 0))
		return (FALSE);
	else if (ft_strchr("<|>&;()", last_char))
		return (!print_error_syntax(sh, last_char, 2));
	return (FALSE);
}

int	prepare_line(t_shell *shell)
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

	shell->status = CONTINUE;
	if (!*shell->user_line)
		return (FALSE);
	add_history(shell->user_line);
	if (syntax_error(shell))
		return (FALSE);
	check_expand(shell, shell->user_line);
	nullterminate(shell, -1);
	return (TRUE);
}
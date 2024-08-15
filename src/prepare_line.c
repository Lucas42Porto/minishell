/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:44:32 by resilva           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/15 00:20:37 by lumarque         ###   ########.fr       */
=======
/*   Updated: 2024/08/14 22:07:29 by resilva          ###   ########.fr       */
>>>>>>> renan-branch
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	nullterminate(t_shell *sh, int i)
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

static int	expand_parse(t_shell *shell, char *line, int i)
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

static void	check_expand(t_shell *shell, char *line)
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

static int	syntax_error(t_shell *sh, char *line, int squote, int dquote)
{
	char	last_char;
	
	last_char = line[ft_strlen(line) - 1];
	if (ft_strchr(BAD_OP, *line))
		return (print_error_syntax(sh, line, 2));
	
	while (*line)
	{
		if (*line == '"' && !squote)
			dquote = !dquote;
		else if (*line == '\'' && !dquote)
			squote = !squote;
<<<<<<< HEAD
		if (!squote && !dquote && ((*line == '|' && *(line + 1) == '|') \
			|| *line == '&' || *line == ';'))
=======
		if (!squote && !dquote && ((*line == '|' && *(line + 1) == '|') || *line == '&' || *line == ';'))
>>>>>>> renan-branch
			return (print_error_syntax(sh, line, 2));
		line++;
	}
	if (squote || dquote)
		return (print_error(sh, ERROR_QUOTE, NULL, 2));
	
	if (ft_strchr(BAD_OP, last_char))
		return (print_error_syntax(sh, --line, 2));
	return (FALSE);
}

int	prepare_line(t_shell *shell)
{
	shell->status = CONTINUE;
	if (!*shell->user_line)
		return (FALSE);
	add_history(shell->user_line);
	if (syntax_error(shell, shell->user_line, 0, 0))
		return (FALSE);
	check_expand(shell, shell->user_line);
	nullterminate(shell, -1);
	return (TRUE);
}
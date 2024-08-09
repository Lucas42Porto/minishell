/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:53:15 by resilva           #+#    #+#             */
/*   Updated: 2024/07/09 21:53:15 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	g_exit;

void	get_userline(t_shell *shell, char *prompt)
{
	prompt = "[minishell]~> ";
	shell->user_line = readline(prompt);
	shell->user_line = ft_strtrim(shell->user_line, SPACES);
	if (!shell->user_line)
		clean_exit(shell, NULL);
}

int main (void)
{
	t_shell	shell;

	init_env_and_path(&shell, &shell.env);
	while(1) 
	{
		get_userline(&shell, NULL);
		if (*shell.user_line)
		{
			add_history(shell.user_line);
			if (!lexer(&shell))
				continue;
			if (parse(&shell))
			{
				ft_exec_cmd(&shell, shell.user_line);
			}
		}
	}
	return 0;
}
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

void	get_userline(t_shell *shell, char *prompt)
{
	prompt = "[minishell]~> ";
	shell->user_line = ft_strtrim(readline(prompt), SPACES);
	if (!shell->user_line)
		clean_exit(shell, NULL);
	shell->size_line = ft_strlen(shell->user_line);
}

int main (void)
{
	t_shell	shell;

	init_env_and_path(&shell, &shell.env);
	while(1) 
	{
		get_userline(&shell, NULL);


	// 	if (ft_strncmp(shell.user_line, "", shell.size_line) == 0)
	// 		continue;
	// 	if (shell.size_line > 0)
	// 		add_history(shell.user_line);
	// 	if (!lexer(&shell))
	// 		continue;
	// 	//ft_skip_space(&shell.user_line);
	// 	ft_exec_cmd(&shell, shell.user_line);

		if (*shell.user_line)
		{
			add_history(shell.user_line);
			if (!lexer(&shell))
				continue;
			ft_exec_cmd(&shell, shell.user_line);
		}
	}
	return 0;
}
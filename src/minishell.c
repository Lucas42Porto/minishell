/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:28:39 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/07 01:41:11 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
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

#include "../include/minishell.h"

int			g_exit;

void	get_userline(t_shell *shell, char *prompt)
{
	prompt = "[minishell]~> ";
	shell->user_line = readline(prompt);
	shell->user_line = ft_strtrim(shell->user_line, SPACES);
	if (!shell->user_line)
		clean_exit(shell, NULL);
}

int	run_ms(t_shell *shell)
{
	shell->status = STOP;
	get_userline(shell, NULL);
	if (shell->user_line && prepare_line(shell))
	{
		if (parse(shell))
		{
			//run_cmd(shell, shell->cmd);
		}
	}
	free(shell->user_line);
	return (shell->status);
}

int main(void)
{
	t_shell	shell;

	init_env_and_path(&shell, &shell.env);
	while(run_ms(&shell))
		;
	clear_history();
	return 0;
}
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

t_shell	*get_shell(t_shell *new_sh)
{
	static t_shell	*shell = NULL;

	if (new_sh)
		shell = new_sh;
	return (shell);
}

static void	get_userline(t_shell *shell, char *prompt)
{
	char	*tmp;

	prompt = ft_strdup("minishell➜ ");
	shell->user_line = readline(prompt);
	tmp = shell->user_line;
	shell->user_line = ft_strtrim(shell->user_line, SPACES);
	free(tmp);
	free(prompt);
}

static int	run_ms(t_shell *shell)
{
	signal_handler(SIGRESTORE);
	shell->status = STOP;
	get_userline(shell, NULL);
	get_shell(shell);
	if (shell->user_line && prepare_line(shell))
	{
		if (parse(shell))
		{
			signal_handler(SIGPIPE);
			run_cmd(shell, shell->cmd);
		}
		free_cmd(shell->cmd);
	}
	free(shell->user_line);
	return (shell->status);
}

int	main(void)
{
	t_shell	shell;

	init_shell_and_env(&shell, &shell.env);
	while (run_ms(&shell))
		;
	clear_history();
	free_env(&shell.env);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (shell.oldpwd)
		free(shell.oldpwd);
	return (g_exit);
}

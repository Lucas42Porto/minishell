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

char	*ft_strnstr2(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[h] != '\0')
	{
		n = 0;
		while (haystack[h + n] == needle[n] && (h + n) < len)
		{
			if (haystack[h + n] == '\0' && needle[n] == '\0')
				return ((char *)&haystack[h]);
			n++;
		}
		if (needle[n] == '\0')
			return ((char *)haystack + h + n);
		h++;
	}
	return (0);
}

static void	get_userline(t_shell *shell, char *prompt)
{
	prompt = ft_strdup(GREEN "minishell➜ " WHITE);
	shell->user_line = readline(prompt);
	shell->user_line = ft_strtrim(shell->user_line, SPACES);
	if (!shell->user_line)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		clean_exit(shell);
	}
}

static int	run_ms(t_shell *shell)
{
	signal_handler(SIGRESTORE);
	shell->status = STOP;
	get_userline(shell, NULL);
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

	g_exit = 0;
	ft_bzero(&shell, sizeof(t_shell));
	init_env_and_path(&shell, &shell.env);
	while (run_ms(&shell))
		;
	clear_history();
	return (g_exit);
}

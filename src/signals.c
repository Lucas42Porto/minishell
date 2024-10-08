/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:03:00 by lumarque          #+#    #+#             */
/*   Updated: 2024/09/01 16:38:03 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_quit(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
}

static void	sigrestore(int sig)
{
	(void)sig;
	g_exit = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sig_here_doc(int sig)
{
	t_shell	*shell;

	if (sig == SIGINT)
	{
		shell = get_shell(NULL);
		if (shell)
			free_all(shell);
		exit(130);
	}
}

static void	sigint_ignore(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		ft_putstr_fd("\n", 2);
		signal(SIGINT, SIG_IGN);
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGRESTORE)
	{
		signal(SIGINT, sigrestore);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == SIGHEREDOC)
	{
		signal(SIGINT, sig_here_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == SIGCHILD)
	{
		signal(SIGINT, sig_quit);
		signal(SIGQUIT, sig_quit);
	}
	if (sig == SIGPIPE)
	{
		signal(SIGINT, sigint_ignore);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == SIGIGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

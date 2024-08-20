/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:52:02 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/20 22:25:57 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_builtin(t_shell *shell, t_exec *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ms_echo(cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ms_cd(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ms_pwd(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (ms_export(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ms_unset(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (ms_env(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ms_exit(shell, cmd), 1);
	return (0);
}

void	wait_children(t_shell *shell)
{
	if (waitpid(shell->pid, &g_exit, 0) != -1)
	{
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		else if (WIFSIGNALED(g_exit))
			g_exit = WTERMSIG(g_exit) + 128;
	}
	while (wait(0) != -1)
		;
	if (g_exit == 130)
		shell->status = RESTORE;
}

static void	close_fds_and_sig_handler(int fd[2], int sig)
{
	if (sig)
		signal_handler(sig);
	check(close(fd[0]), "close error", 127);
	check(close(fd[1]), "close error", 127);
}

void	run_pipe(t_shell *shell, t_pipe *cmd)
{
	int	fd[2];

	check(pipe(fd), "pipe error", 127);
	shell->pid = check_fork();
	if (shell->pid == 0)
	{
		check(dup2(fd[1], STDOUT_FILENO), "dup2 error", 127);
		close_fds_and_sig_handler(fd, SIGIGNORE);
		run_cmd(shell, cmd->left);
		free_exit(shell);
	}
	if (cmd->left->type == HEREDOC)
		wait_children(shell);
	if (shell->status == CONTINUE)
		shell->pid = check_fork();
	if (shell->pid == 0)
	{
		check(dup2(fd[0], STDIN_FILENO), "dup2 error", 127);
		close_fds_and_sig_handler(fd, SIGIGNORE);
		run_cmd(shell, cmd->right);
		free_exit(shell);
	}
	close_fds_and_sig_handler(fd, 0);
	wait_children(shell);
}

void	run_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type == EXEC)
		run_exec(shell, (t_exec *)cmd);
	else if (cmd->type == REDIR)
		run_redir(shell, (t_redir *)cmd);
	else if (cmd->type == HEREDOC)
		run_heredoc(shell, (t_here *)cmd);
	else if (cmd->type == PIPE)
		run_pipe(shell, (t_pipe *)cmd);
}

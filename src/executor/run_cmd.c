/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:52:02 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/06 11:17:08 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishel_2.h"

//corrigir funcoes
// int	run_builtin(t_shell *shell, t_exec *cmd)
// {
// 	if (!ft_strcmp(cmd->argv[0], "echo"))
// 		return (ms_echo(cmd), 1);
// 	else if (!ft_strcmp(cmd->argv[0], "cd"))
// 		return (ms_cd(shell, cmd), 1);
// 	else if (!ft_strcmp(cmd->argv[0], "pwd"))
// 		return (ms_pwd(shell, cmd), 1);
// 	else if (!ft_strcmp(cmd->argv[0], "export"))
// 		return (ms_export(shell, cmd), 1);
// 	else if (!ft_strcmp(cmd->argv[0], "unset"))
// 		return (ms_unset(shell, cmd), 1);
// 	else if (!ft_strcmp(cmd->argv[0], "env"))
// 		return (ms_env(shell, cmd), 1);
// 	else if (!ft_strcmp(cmd->argv[0], "exit"))
// 		return (ms_exit(shell, cmd), 1);
// 	return (0);
// }

void	execute_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->tokens[0], "exit", 4))
		execute_exit(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "echo", 4))
		execute_echo(msh);
	if (!ft_strncmp(msh->tokens[0], "pwd", 3) && !have_options(msh, 0))
		execute_pwd(msh, NULL);
	if (!ft_strncmp(msh->tokens[0], "export", 6) && !have_options(msh, 0))
	{
		if (!msh->tokens[1])
			export_without_args(msh);
		else
			execute_export(msh, 0, NULL);
	}
	if (!ft_strncmp(msh->tokens[0], "unset", 5) && !have_options(msh, 0))
		execute_unset(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "env", 3))
		execute_env(msh, -1);
	if (!ft_strncmp(msh->tokens[0], "cd", 2))
	{
		if (msh->tokens[1] && msh->tokens[2])
			print_error(ERROR_ARG, msh->tokens[0], 1);
		else
			execute_cd(msh, NULL);
	}
}
static void	close_fds_and_sig_handler(int fd[2], int sig)
{
	if (sig)
		sig_handler(sig);
	check(close(fd[0]), "close error", 127);
	check(close(fd[1]), "close error", 127);
}

static void	run_pipe(t_shell *shell, t_pipe *cmd)
{
	int		fd[2];

	check(pipe(fd), "pipe error", 127);
	shell->pid = check_fork();
	if (shell->pid == 0)
	{
		check(dup2(fd[1], STDOUT_FILENO), "dup2 error", 127);
		close_fds_and_sig_handler(fd, SIGIGNORE);
		run_cmd(shell, cmd->left);
		free_exit(shell);
	}
	if (cmd->left->type == HERE_DOC)
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
	if (cmd->type == EXEC && shell->exec_cmd == true)
		run_exec(shell, (t_exec *)cmd);
	else if (cmd->type == REDIR && shell->exec_cmd == true)
		run_redir(shell, (t_redir *)cmd);
	else if (cmd->type == HERE_DOC)
		run_heredoc(shell, (t_here *)cmd);
	else if (cmd->type == PIPE)
		run_pipe(shell, (t_pipe *)cmd);
	else if (cmd->type == BLOCK && shell->exec_cmd == true)
		run_block(shell, (t_block *)cmd);
}
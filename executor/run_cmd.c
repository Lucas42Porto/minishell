/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:52:02 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/09 22:54:23 by resilva          ###   ########.fr       */
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
	if (waitpid(shell->pid, &g_exit, 0) != -1) // Espera o processo filho terminar.
	{
		if (WIFEXITED(g_exit)) // Se o processo filho terminou normalmente.
			g_exit = WEXITSTATUS(g_exit);
		else if (WIFSIGNALED(g_exit))
			g_exit = WTERMSIG(g_exit) + 128; // Obtém o sinal que causou a terminação do processo filho.
	}
	while (wait(0) != -1) // Espera todos os processos filhos terminarem.
		;
	if (g_exit == 130) // Se o sinal for SIGINT.
		shell->status = RESTORE; // O status é RESTORE. Senão o status é CONTINUE. Qual a diferença? O status RESTORE é usado para restaurar o prompt após um sinal SIGINT. O status CONTINUE é usado para continuar a execução do shell. Em termos práticos o que acontece? Se o utilizador carregar ctrl+c, o shell continua a correr. Se o utilizador carregar ctrl+d, o shell fecha. Porquê? Porque o ctrl+d é um sinal de EOF. O que é EOF? EOF é o fim do ficheiro. Se o utilizador carregar ctrl+d, o shell fecha. Se o utilizador carregar ctrl+c, o shell continua a correr. Porquê? Porque o ctrl+c é um sinal de interrupção. Se o utilizador carregar ctrl+c, o shell continua a correr.
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
	if (cmd->left->type == HEREDOC) // Se o tipo do comando da esquerda for HERE_DOC.
		wait_children(shell); // Espera o processo filho terminar.
	if (shell->status == CONTINUE) // Se o status for CONTINUE.
		shell->pid = check_fork(); // Cria um novo processo filho, que será o comando da direita.
	if (shell->pid == 0)
	{
		check(dup2(fd[0], STDIN_FILENO), "dup2 error", 127);
		close_fds_and_sig_handler(fd, SIGIGNORE);
		run_cmd(shell, cmd->right);
		free_exit(shell);
	}
	close_fds_and_sig_handler(fd, 0); // Fecha os descritores de arquivo.
	wait_children(shell); // Espera o processo filho terminar.
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
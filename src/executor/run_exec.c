/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:58:55 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/08 01:09:27 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_execve_errors(t_shell *shell, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (!access(path, F_OK) && access(path, X_OK) && ft_strchr(path, '/'))
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (!access(path, F_OK) && !access(path, X_OK) && path[0] != '.')
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else if (ft_strchr(path, '/') || !env_get("PATH", shell))
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else
		ft_putendl_fd(": command not found", STDERR_FILENO);
	g_exit = 127
		- ((!access(path, F_OK) && access(path, X_OK)) || !access(path, F_OK));
	free(path);
	free_exit(shell);
}

static char	*get_path(t_shell *sh, char *cmd)
{
	int		i;
	char	*path;
	char	*path2;
	char	**paths;

	i = 0;
	path = NULL;
	path2 = NULL;
	if (ft_strchr("/.", cmd[0]) || !env_get("PATH", sh) || !ft_strcmp(cmd, ""))
		return (ft_strdup(cmd));
	paths = ft_split(env_get("PATH", sh), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path2 = ft_strjoin(path, cmd);
		free(path);
		path = NULL;
		if (!access(path2, F_OK))
			return (path2);
		free(path2);
		path2 = NULL;
		i++;
	}
	ft_free_array(paths);
	return (ft_strdup(cmd));
}

static void	check_exit_status(void)
{
	if (g_exit == 11 || g_exit == 139)
		ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
	else if (g_exit == 8 || g_exit == 136)
		ft_putendl_fd("Floating point exception (core dumped)", STDERR_FILENO);
}

static void	expand_argv(t_shell *shell, char **argv)
{
	int		len;
	int		i;
	int		expanded;
	char	*tmp;

	if (!argv[0])
		return ;
	expanded = (ft_strchr(argv[0], '$') || ft_strchr(argv[0], '*'));
	expand_arg(shell, &argv[0]);
	len = ft_strlen(argv[0]);
	trim_arg(argv[0]); // Esta função insere um caractere nulo em cada espaço em branco que não está entre aspas. Se na parseexec retiramos os nulos para colocar espaços, aqui fazemos o contrário.
	trim_quotes(argv[0], &len); // Remover aspas
	i = 1;
	tmp = argv[0];
	while ((tmp < argv[0] + len) && i < (MAXARGS - 1)) 
	{
		if (*tmp == '\0' && (ft_strcmp(argv[0], "printf") || i != 2))
			argv[i++] = tmp + 1;
		tmp++;
	}
	if (!argv[0][0] && expanded) // $EMPTY_VAR. Neste caso a função expande, mas verifica que a expansão não expande para lado nenhum uma vez que a variável não existe. Nestes casos dá free e coloca o argumento a NULL.
	{
		free(argv[0]);
		argv[0] = NULL;
	}
}

void	run_exec(t_shell *shell, t_exec *cmd)
{
	pid_t	pid;
	char	*path;

	expand_argv(shell, cmd->argv);
	if (!cmd->argv[0])
		return (g_exit = 0, (void)0);
	if (run_builtin(shell, cmd))
		return ;
	sig_handler(SIGCHILD);
	pid = check_fork();
	if (pid == 0)
	{
		path = get_path(shell, cmd->argv[0]); // cmd_path = ft_strdup(msh->paths[i]);
		execve(path, cmd->argv, shell->envp);
		check_execve_errors(shell, path);
	}
	waitpid(pid, &g_exit, 0);
	if (WIFEXITED(g_exit)) // Se o processo filho terminou normalmente.
		g_exit = WEXITSTATUS(g_exit); // Retorna o status de saída do processo filho.
	else if (WIFSIGNALED(g_exit)) // Se o processo filho foi encerrado por um sinal.
		g_exit = 128 + WTERMSIG(g_exit); // Retorna o sinal que encerrou o processo filho.
	check_exit_status(); // Esta função verifica se houve erros na execução do comando.
	signal_handler(SIGRESTORE); // Esta função trata os sinais, que mudam para o modo de execução de um processo pai.
}
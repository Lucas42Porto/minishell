/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:09:44 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/13 20:57:28 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
		perror("fork");
		g_exit = 127;
	}
	return (pid);
}

// Esta função expande o here_doc. Ela percorre a linha e verifica se o caractere atual é um til ou uma variável de ambiente. Se o caractere atual for um til, a função expand é chamada para expandir o til. Se o caractere atual for uma variável de ambiente, a função expand é chamada para expandir a variável de ambiente.
static void	expand_heredoc(char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			tmp = ft_itoa(g_exit);
			expand(tmp, i, i + 2, line);
			free(tmp);
		}
		else if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
		{
			j = i + 1;
			while (ft_isalnum((*line)[j]) || (*line)[j] == '_')
				j++;
			tmp = ft_substr(*line, i + 1, j - i - 1);
			expand(getenv(tmp), i, j, line);
			free(tmp);
		}
		i++;
	}
}

// Em seguida, a linha é impressa no arquivo "here_doc" e a memória alocada para a linha é liberada. Após o loop, o descritor de arquivo é fechado e a variável global g_exit é definida como 0. Por fim, a função free_exit é chamada.
static void	heredoc_reader(t_shell *shell, t_here *here, int fd)
{
	char	*line;

	fd = open("here_doc", here->mode, 0644); //Ela abre o arquivo "here_doc" com o modo de leitura e escrita
	dup2(here->fdin, STDIN_FILENO);
	dup2(here->fdout, STDOUT_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf(ERROR_HEAD ERROR_HERE_DOC "%s'\n", here->eof);
			break ;
		}
		if (ft_strcmp(line, here->eof) == 0)
		{
			free(line);
			break ;
		}
		expand_heredoc(&line); // a função expand_heredoc é chamada para expandir as variáveis de ambiente e o til.
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	g_exit = 0;
	free_exit(shell);
}

void	run_heredoc(t_shell *shell, t_here *here)
{
	int		fd;
	int		len;
	pid_t	pid;

	len = ft_strlen(here->eof);
	trim_quotes(here->eof, &len);
	pid = check_fork(); // Verifica e cria um processo filho
	if (pid == 0)
	{
		signal_handler(SIGHEREDOC); //chama a função signal_handler para definir o sinal SIGHEREDOC
		heredoc_reader(shell, here, 0);
	}
	waitpid(pid, &g_exit, 0);
	g_exit = WEXITSTATUS(g_exit);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (g_exit == 0)
		run_cmd(shell, here->cmd);
	dup2(here->fdin, STDIN_FILENO);
	unlink("here_doc");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:39:09 by crocha-s          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:12 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	envp_print(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
	{
		ft_putstr_fd(shell->env.e_name[i], STDIN_FILENO);
		ft_putchar_fd('=', STDIN_FILENO);
		ft_putstr_fd(shell->env.e_content[i], STDIN_FILENO);
		ft_putchar_fd('\n', STDIN_FILENO);	
		}
}
// A função ms_env verifica se o comando tem argumentos. Se o comando tiver argumentos, a função imprime um erro. Se o comando não tiver argumentos, a função verifica se a variável de ambiente PATH existe. Se a variável de ambiente PATH existir (o que é verificado na função env_get), a função entra no loop da função env_print e imprime todas as variáveis de ambiente que encontrar. Se a variável de ambiente PATH não existir, a função imprime um erro.
void	ms_env(t_shell *shell, t_exec *cmd)
{
	if (cmd->argv[1])
		print_error(shell, "env", "too many arguments", 2);
	else
	{
		if (getenv("PATH")) // Se a variável de ambiente PATH existir (o que é verificado na função get)...
			envp_print(shell); // ... imprime todas as variáveis de ambiente.
		else
			print_error(shell, cmd->argv[0], "No such file or directory", 127); // Caso contrário, imprime um erro.
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}

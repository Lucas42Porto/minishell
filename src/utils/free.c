/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:31:28 by resilva           #+#    #+#             */
/*   Updated: 2024/08/09 22:31:51 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_shell *shell, char *exit_code)
{
	ft_putstr_fd("exit\n", STDIN_FILENO);
	if (shell->paths)
		free_split(shell->paths);
	free_split(shell->env.e_name);
	free_split(shell->env.e_content);
	free(shell->user_line);
	if (exit_code)
		exit(ft_atoi(exit_code));
	exit(EXIT_SUCCESS);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
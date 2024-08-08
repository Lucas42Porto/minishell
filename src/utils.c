/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:01:31 by resilva           #+#    #+#             */
/*   Updated: 2024/08/09 00:23:27 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(char *header, char *subheader, char *msg)
{
	ft_putstr_fd(header, 2);
	ft_putstr_fd(": ", 2);
	if (subheader)
	{
		ft_putstr_fd(subheader, 2);
		ft_putstr_fd(": ", 2);
	}		
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

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


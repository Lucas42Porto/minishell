/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:31:28 by resilva           #+#    #+#             */
/*   Updated: 2024/08/21 00:59:37 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_env(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->size_env)
	{
		free(env->e_name[i]);
		if (env->e_content[i])
			free(env->e_content[i]);
	}
	free(env->e_name);
	free(env->e_content);
}

void	clean_exit(t_shell *shell)
{
	free_cmd(shell->cmd);
	free_env(&shell->env);
	free(shell->user_line);
	if (shell->oldpwd)
		free(shell->oldpwd);
	exit(g_exit);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		if (split[i])
			free(split[i]);
	free(split);
}

void	free_exit(t_shell *shell)
{
	if (shell->user_line)
		free(shell->user_line);
	free_cmd(shell->cmd);
	exit(g_exit);
}

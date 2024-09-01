/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:31:28 by resilva           #+#    #+#             */
/*   Updated: 2024/08/31 15:37:38 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_env *env)
{
	int	i;

	i = -1;
	if (!env || !env->e_name || !env->e_content)
		return ;
	while (++i < env->size_env)
	{
		free(env->e_name[i]);
		env->e_name[i] = NULL;
		if (env->e_content[i])
		{
			free(env->e_content[i]);
			env->e_content[i] = NULL;
		}
	}
	free(env->e_name);
	env->e_name = NULL;
	free(env->e_content);
	env->e_content = NULL;
}

void	clean_exit(t_shell *shell)
{
	if (shell->cmd)
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

void	free_all(t_shell *shell)
{
	free_env(&shell->env);
	if (shell->cmd)
	{
		free_cmd(shell->cmd);
		shell->cmd = NULL;
	}
	if (shell->user_line)
	{
		free(shell->user_line);
		shell->user_line = NULL;
	}
	if (shell->oldpwd)
	{
		free(shell->oldpwd);
		shell->oldpwd = NULL;
	}
}

void	free_exit(t_shell *shell)
{
	free_all(shell);
	exit(g_exit);
}

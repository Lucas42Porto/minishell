/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:26:50 by resilva           #+#    #+#             */
/*   Updated: 2024/08/29 17:44:30 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_env(t_env *env, t_env *env_copy)
{
	int	i;

	i = -1;
	if (!env_copy)
		exit(EXIT_FAILURE);
	env_copy->e_name = malloc(sizeof(char *) * (env->size_env + 1));
	env_copy->e_content = malloc(sizeof(char *) * (env->size_env + 1));
	if (!env_copy->e_name || !env_copy->e_content)
		exit(EXIT_FAILURE);
	while (++i < env->size_env)
	{
		env_copy->e_name[i] = ft_strdup(env->e_name[i]);
		if (!env->e_content[i])
			env_copy->e_content[i] = NULL;
		else
			env_copy->e_content[i] = ft_strdup(env->e_content[i]);
	}
	env_copy->e_name[i] = NULL;
	env_copy->e_content[i] = NULL;
	env_copy->size_env = env->size_env;
}

static void	new_env(t_env *env, char *name, char *new_value)
{
	int	old_size_env;

	old_size_env = sizeof(char *) * (env->size_env);
	env->e_name = ft_realloc(env->e_name, sizeof(char *) * \
			(env->size_env + 1), old_size_env);
	env->e_content = ft_realloc(env->e_content, sizeof(char *) * \
			(env->size_env + 1), old_size_env);
	env->e_name[env->size_env] = ft_strdup(name);
	if (!new_value)
		env->e_content[env->size_env] = NULL;
	else
		env->e_content[env->size_env] = ft_strdup(new_value);
	env->size_env++;
}

void	update_env(t_env *env, char *name, char *new_value)
{
	int	i;

	i = 0;
	while (i < env->size_env)
	{
		if (!ft_strcmp(env->e_name[i], name))
		{
			free(env->e_content[i]);
			if (new_value)
				env->e_content[i] = ft_strdup(new_value);
			else
				env->e_content[i] = NULL;
			return ;
		}
		i++;
	}
	new_env(env, name, new_value);
}

static void	swap(char **x, char **y)
{
	char	*temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void	selection_sort_env(t_env *env, int i, int j)
{
	int	min_idx;

	while (++i < env->size_env)
	{
		min_idx = i;
		j = i + 1;
		while (j < env->size_env)
		{
			if (ft_strcmp(env->e_name[j], env->e_name[min_idx]) < 0)
				min_idx = j;
			j++;
		}
		swap(&env->e_name[i], &env->e_name[min_idx]);
		swap(&env->e_content[i], &env->e_content[min_idx]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:26:50 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 16:01:08 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env(t_env *env, char *name, char *new_value)
{
	int	i;
	int	old_size_env;

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
	// Caso a variável não exista, adiciona nova variável ao env
	old_size_env = sizeof(char *) * env->size_env;
	env->e_name = ft_realloc(env->e_name, sizeof(char *) * (env->size_env + 1), old_size_env);
	env->e_content = ft_realloc(env->e_content, sizeof(char *) * (env->size_env + 1), old_size_env);
	
	env->e_name[env->size_env] = ft_strdup(name);
	if (!new_value)
		env->e_content[env->size_env] = NULL;
	else
		env->e_content[env->size_env] = ft_strdup(new_value);
	env->size_env++;
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
    int min_idx;

	while (++i < env->size_env - 1)
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

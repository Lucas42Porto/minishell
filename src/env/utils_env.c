/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:42:00 by resilva           #+#    #+#             */
/*   Updated: 2024/08/29 18:07:38 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_get(t_env *env, char *name)
{
	int	i;

	i = -1;
	while (++i < env->size_env)
	{
		if (!ft_strcmp(env->e_name[i], name))
			return (env->e_content[i]);
	}
	return (NULL);
}

char	*env_get_exp(t_env *env, char *name)
{
	int	i;

	i = -1;
	while (++i < env->size_env)
	{
		if (!ft_strcmp(env->e_name[i], "HOME") \
			&& env->e_content[i] == NULL)
			return (NULL);
		else if (!ft_strcmp(env->e_name[i], "HOME") \
			&& !ft_strcmp(env->e_content[i], "~"))
			return (NULL);
		else if (!ft_strcmp(env->e_name[i], name))
			return (env->e_content[i]);
	}
	return (NULL);
}

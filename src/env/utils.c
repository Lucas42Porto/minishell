/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:42:00 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 01:02:07 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_get(t_env *env, char *name)
{
	int	i;

	i = -1;
	while (++i < env->size_env - 1)
	{
		if (!ft_strcmp(env->e_name[i], name))
			return (env->e_content[i]);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:26:52 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:10:19 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_unset_name(t_shell *sh, char *arg, int i)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (!print_error_export(sh, "unset", arg, 1));
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (!print_error_export(sh, "unset", arg, 1));
	}
	return (TRUE);
}

static void	unset_var(t_env *env, char *arg, int i)
{
	int	j;
	int	old_size_env;

	while (++i < env->size_env - 1)
	{
		if (!ft_strcmp(env->e_name[i], arg))
		{
			free(env->e_name[i]);
			free(env->e_content[i]);
			j = i;
			while (j < env->size_env - 1)
			{
				env->e_name[j] = env->e_name[j + 1];
				env->e_content[j] = env->e_content[j + 1];
				j++;
			}
			old_size_env = sizeof(char *) * env->size_env;
			env->size_env--;
			env->e_name = ft_realloc(env->e_name, sizeof(char *) * \
				env->size_env, old_size_env);
			env->e_content = ft_realloc(env->e_content, sizeof(char *) * \
				env->size_env, old_size_env);
			return ;
		}
	}
}

void	ms_unset(t_shell *shell, t_exec *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (valid_unset_name(shell, cmd->argv[i], -1))
			unset_var(&shell->env, cmd->argv[i], -1);
		i++;
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:33:07 by resilva           #+#    #+#             */
/*   Updated: 2024/08/26 01:15:20 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_var(t_shell *sh, char *arg)
{
	char	*equal;
	char	*name;
	char	*value;

	value = NULL;
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*equal = '\0';
		name = ft_strdup(arg);
		value = ft_strdup(equal + 1);
		update_env(&sh->env, name, value);
	}
	else
	{
		name = ft_strdup(arg);
		update_env(&sh->env, name, NULL);
	}
	free(name);
	if (value)
		free(value);
}

static int	valid_export_name(t_shell *sh, char *arg, int i)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (!print_error_export(sh, "export: ", arg, 1));
	while (arg[++i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (!print_error_export(sh, "export: ", arg, 1));
	}
	return (TRUE);
}

static t_env	*copy_env(t_env *env, t_env *env_copy)
{
	int	i;

	i = -1;
	env_copy = (t_env *)malloc(sizeof(t_env));
	if (!env_copy)
		exit(EXIT_FAILURE);
	env_copy->e_name = malloc(sizeof(char *) * (env->size_env + 1));
	env_copy->e_content = malloc(sizeof(char *) * (env->size_env + 1));
	if (!env_copy->e_name || !env_copy->e_content)
		exit(EXIT_FAILURE);
	while (++i < env->size_env)
	{
		env_copy->e_name[i] = ft_strdup(env->e_name[i]);
		if (env->e_content[i])
			env_copy->e_content[i] = ft_strdup(env->e_content[i]);
	}
	env_copy->e_name[i] = NULL;
	env_copy->e_content[i] = NULL;
	env_copy->size_env = env->size_env;
	return (env_copy);
}

static void	print_export(t_env *env, int i)
{
	t_env	*env_sort;

	env_sort = NULL;
	env_sort = copy_env(env, NULL);
	selection_sort_env(env_sort, -1, 0);
	while (++i < env_sort->size_env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_sort->e_name[i], STDOUT_FILENO);
		if (env_sort->e_content[i])
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_sort->e_content[i], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	free_env(env_sort);
	free(env_sort);
}

void	ms_export(t_shell *shell, t_exec *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[1])
		print_export(&shell->env, -1);
	else
	{
		while (cmd->argv[i])
		{
			if (valid_export_name(shell, cmd->argv[i], -1))
				export_var(shell, cmd->argv[i]);
			i++;
		}
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}

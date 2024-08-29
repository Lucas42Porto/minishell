/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:33:07 by resilva           #+#    #+#             */
/*   Updated: 2024/08/29 18:25:12 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	specific_update(t_shell *sh, char **name, char **value)
{
	if (!sh->exp_quote && !ft_strcmp(*name, "HOME") \
		&& !ft_strcmp(*value, "~"))
	{
		free(*value);
		*value = env_get(&sh->env, "HOME");
		if (*value)
			*value = ft_strdup(*value);
	}
	update_env(&sh->env, *name, *value);
}

static void	export_var(t_shell *sh, char *arg, char *name, char *value)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*equal = '\0';
		name = ft_strdup(arg);
		value = ft_strdup(equal + 1);
		specific_update(sh, &name, &value);
	}
	else if (!env_get(&sh->env, arg))
	{
		name = ft_strdup(arg);
		update_env(&sh->env, name, NULL);
	}
	if (name)
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

static void	print_export(t_env *env, t_env *env_sort, int i)
{
	copy_env(env, env_sort);
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
}

void	ms_export(t_shell *shell, t_exec *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[1])
		print_export(&shell->env, &shell->env_sort, -1);
	else
	{
		while (cmd->argv[i])
		{
			if (valid_export_name(shell, cmd->argv[i], -1))
				export_var(shell, cmd->argv[i], NULL, NULL);
			i++;
		}
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}

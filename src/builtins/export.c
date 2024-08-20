/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:33:07 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 21:08:11 by resilva          ###   ########.fr       */
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
			break;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (!print_error_export(sh, "export: ", arg, 1));
	}
	return (TRUE);
}

static void	print_export(t_env *env, int i)
{
	selection_sort_env(env, -1, 0);
	while (++i < env->size_env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->e_name[i], STDOUT_FILENO);
		if (env->e_content[i])
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->e_content[i], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:58:48 by resilva           #+#    #+#             */
/*   Updated: 2024/09/01 23:19:42 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	arg_insert_null(char *arg)
{
	int	quote;

	quote = 0;
	while (*arg)
	{
		if ((*arg == '"' || *arg == '\'') && !quote)
			quote = *arg;
		else if (quote == *arg)
			quote = 0;
		if (ft_strchr(SPACES, *arg) && !quote)
			*arg = '\0';
		arg++;
	}
}

void	trim_quotes(t_shell *sh, char *arg, int *len)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < *len)
	{
		if ((arg[i] == '"' || arg[i] == '\'') && !quote)
		{
			sh->flag_quote = 1;
			quote = arg[i];
			ft_memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else if (quote && arg[i] == quote)
		{
			quote = 0;
			ft_memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else
			i++;
	}
}

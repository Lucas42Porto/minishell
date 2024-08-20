/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:58:39 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:54:07 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expand(char *key, int i, int j, char **line)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(*line, 0, i);
	tmp2 = ft_substr(*line, j, ft_strlen(*line) - j + 1);
	tmp3 = *line;
	free(tmp3);
	*line = ft_strjoin(tmp, key);
	free(tmp);
	tmp = *line;
	*line = ft_strjoin(*line, tmp2);
	free(tmp);
	free(tmp2);
	return (1);
}

int	expand_free(char *key, int i, int j, char **line)
{
	expand(key, i, j, line);
	free(key);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:26:00 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/15 02:26:10 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Esta função expande a linha inserindo uma chave entre os índices 'i' e 'j'.
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

// Esta função expande a linha inserindo uma chave entre os índices 'i' e 'j', dando free na chave.
int	expand_free(char *key, int i, int j, char **line)
{
	expand(key, i, j, line);
	free(key);
	return (1);
}

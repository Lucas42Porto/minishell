/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:10:46 by lumarque          #+#    #+#             */
/*   Updated: 2023/05/06 18:39:40 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != sep)
		{
			words++;
			while (s[i] && s[i] != sep)
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	*word_cpy(const char *str, char sep)
{
	char	*word;
	int		wdlen;
	int		i;

	wdlen = 0;
	while (str[wdlen] && (str[wdlen] != sep))
		wdlen++;
	word = (char *) malloc(sizeof(char) * (wdlen + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && (str[i] != sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**words;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	words = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			words[j] = word_cpy(&s[i], c);
			while (s[i] && (s[i] != c))
				i++;
			j++;
		}
		else
			i++;
	}
	words[j] = 0;
	return (words);
}

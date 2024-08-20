/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:30:42 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/19 23:05:28 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	c = (char *)malloc(len * sizeof(char) + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		c[i + j] = s2[j];
		j++;
	}
	c[i + j] = '\0';
	return (c);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*dst;
// 	int		i;
// 	int		j;

// 	dst = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!dst || !s1 || !s2)
// 		return (0);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		dst[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != '\0')
// 	{
// 		dst[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

/*int main()
{
	printf("%s\n", ft_strjoin("42", "Porto"));
    return (0);
}*/
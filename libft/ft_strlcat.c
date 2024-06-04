/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:30:38 by lumarque          #+#    #+#             */
/*   Updated: 2023/04/19 20:12:06 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	size_dst;
	unsigned int	size_src;

	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	if (size <= size_dst)
		return (size + size_src);
	i = size_dst;
	j = 0;
	while (src[j] && j < size - size_dst - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (size_dst + size_src);
}

/*int main()
{
    char s1[20] = {"Hello"};
    char s2[20] = {"World"};
 	int n = 8;

 	unsigned int ptr = ft_strlcat(s1, s2, n);

    printf("-----\ns1 = %s\ns2 = %s\n", s1, s2);
 	printf("%d\n", ptr);

     return (0);
}*/
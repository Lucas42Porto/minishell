/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:30:35 by lumarque          #+#    #+#             */
/*   Updated: 2023/04/25 17:40:25 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;

	size_src = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (size_src);
}

/*int main()
{
    char s1[20] = {"HE"};
    char s2[20] = {"World"};
 	int n = 0;
	
	printf("-----\ns1 = %s\ns2 = %s\n", s1, s2);
	printf("%d\n", ft_strlcpy(s1, s2, n));
	//printf("%d\n", strlcpy(s1, s2, n));

     return (0);
}*/
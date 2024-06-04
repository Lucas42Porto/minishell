/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:30:16 by lumarque          #+#    #+#             */
/*   Updated: 2023/05/08 20:07:53 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		l;
	char	*str;

	str = (char *)s;
	l = ft_strlen(s);
	while (l >= 0)
	{
		if (str[l] == ((char)c))
			return (&str[l]);
		l--;
	}
	return (0);
}

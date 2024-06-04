/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:00:29 by lumarque          #+#    #+#             */
/*   Updated: 2023/04/23 15:55:09 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}

// #include <stdio.h>
// #include <string.h>
// int	test(int i, char *a)
// {
// 	return (!!strcmp(ft_itoa(i), a));
// }
// int	main(void)
// {
// 	if (test(1, "1")
// 		|| test(-1, "-1")
// 		|| test(-10, "-10")
// 		|| test(2147483647, "2147483647")
// 		|| test(-2147483648, "-2147483648")
// 		|| test(0, "0")
// 		|| test(1000, "1000")
// 		|| test(2345, "2345")
// 		|| test(19, "19")
// 		|| test(55, "55")
// 		|| test(-3000, "-3000")
// 		|| test(250000, "250000"))
// 	{
// 		printf("KO: ft_itoa\n");
// 		return (1);
// 	}
// 	printf("OK: ft_itoa\n");
// 	return (0);
// }
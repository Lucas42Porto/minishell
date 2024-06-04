/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:59:35 by lumarque          #+#    #+#             */
/*   Updated: 2023/04/28 21:07:23 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_char(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	num;
	char			*buffer;

	buffer = (char *)malloc(num_of_char(n) + 1);
	if (buffer == NULL)
		return (0);
	i = num_of_char(n);
	num = n;
	if (n < 0)
	{
		num = -n;
		buffer[0] = '-';
	}
	buffer[i] = 0;
	buffer[i - 1] = '0';
	while (num > 0)
	{
		i--;
		buffer[i] = (num % 10) + 48;
		num /= 10;
	}
	return (buffer);
}

/*#include <stdio.h>
#include <string.h>
int	test(int i, char *a)
{
	return (!!strcmp(ft_itoa(i), a));
}
int	main(void)
{
	if (test(1, "1")
		|| test(-1, "-1")
		|| test(-10, "-10")
		|| test(2147483647, "2147483647")
		|| test(-2147483648, "-2147483648")
		|| test(0, "0")
		|| test(1000, "1000")
		|| test(2345, "2345")
		|| test(19, "19")
		|| test(55, "55")
		|| test(-3000, "-3000")
		|| test(250000, "250000"))
	{
		printf("KO: ft_itoa\n");
		return (1);
	}
	printf("OK: ft_itoa\n");
	return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:58:51 by lumarque          #+#    #+#             */
/*   Updated: 2023/04/23 15:10:46 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long			result;
	long			sign;
	unsigned int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' \
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)(result * sign));
}

/*
#include <stdlib.h>
#include <stdio.h>
int	test(char *n)
{
	int		i1;
	int		i2;
	i1 = atoi(n);
	i2 = ft_atoi(n);
	if (0)
		printf("%d %d\n", i1, i2);
	return (i1 == i2);
}
int	main(void)
{
	if (!test("0")
		|| !test("-0")
		|| !test("+0")
		|| !test("-")
		|| !test("+")
		|| !test("a")
		|| !test("+a")
		|| !test("-b")
		|| !test("7")
		|| !test("+7a3")
		|| !test("\t\n\r\v\f  469 \n")
		|| !test("-6O40")
		|| !test("++10")
		|| !test("--10")
		|| !test("2147483647")
		|| !test("-2147483648")
		|| !test("1000000000000")
		|| !test("-1000000000000"))
	{
		printf("KO: ft_atoi\n");
		return (1);
	}
	printf("OK: ft_atoi\n");
	if (!ft_test("9999999999999999999999999999999998"))
		printf("hummm \n");
	printf("or %d\n", atoi("9999999999999999999999999999999998"));
	printf("ft %d\n", ft_atoi("9999999999999999999999999999999998"));
	printf("or %d\n", atoi("1234567891113151719"));
	printf("ft %d\n", ft_atoi("1234567891113151719"));
	printf("or %d\n", atoi("9223372036854775808"));
	printf("ft %d\n", ft_atoi("9223372036854775808"));
	printf("or %d\n", atoi("-2147483649"));
	printf("ft %d\n", ft_atoi("-2147483649"));
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:37:07 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/20 15:51:29 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr_fd(int n, int fd)
{
	int	nbr;

	nbr = n;
	if (n >= 0)
	{
		if (n > 9)
		{
			ft_printnbr_fd(n / 10, fd);
		}
		ft_print_char(n % 10 + 48, fd);
	}
	else if (n == -2147483648)
		ft_print_str("-2147483648", fd);
	else
	{
		ft_print_char('-', fd);
		ft_printnbr_fd(-n, fd);
	}
	return (ft_nbrlen(nbr, 10));
}

static int	ft_nbrlen_ul(unsigned long nbr, unsigned int base)
{
	int	i;

	i = 1;
	while (nbr >= base)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

static int	ft_check_base(const char *base)
{
	if (ft_strlen(base) < 2)
		return (0);
	if (ft_strchr(base, '+') || ft_strchr(base, '-'))
		return (0);
	while (*base)
	{
		if (ft_strchr(base + 1, *base))
			return (0);
		base++;
	}
	return (1);
}

int	ft_putnbase(unsigned long nbr, const char *base, int fd)
{
	unsigned long	n;
	int				size;

	if (!ft_check_base(base))
		return (-1);
	n = (unsigned long)nbr;
	size = (unsigned long)ft_strlen(base);
	if (n >= ft_strlen(base))
		ft_putnbase(n / size, base, fd);
	write(fd, &base[n % size], fd);
	return (ft_nbrlen_ul(nbr, size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:32:57 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/20 15:40:19 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_print_percent(void)
{
	return (write(1, "%", 1));
}

int	ft_print_str(char *s, int fd)
{
	int	len;

	len = 0;
	if (!s)
	{
		ft_print_str("(null)", fd);
		return (6);
	}
	write(fd, s, ft_strlen(s));
	len += ft_strlen(s);
	return (len);
}

size_t	print_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_nbrlen(long nbr, int base)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		i++;
		nbr = -nbr;
	}
	while (nbr >= base)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

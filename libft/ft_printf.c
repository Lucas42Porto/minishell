/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:24:24 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/14 17:49:16 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_address(unsigned long s, int fd)
{
	if (!s)
	{
		ft_print_str("(nil)", fd);
		return (5);
	}
	ft_print_str("0x", fd);
	return (2 + ft_putnbase(s, "0123456789abcdef", fd));
}

static int	ft_formats(va_list args, char flag, int fd)
{
	if (flag == 'c')
		return (ft_print_char(va_arg(args, int), fd));
	else if (flag == 's')
		return (ft_print_str(va_arg(args, char *), fd));
	else if (flag == 'd' || flag == 'i')
		return (ft_printnbr_fd(va_arg(args, int), fd));
	else if (flag == 'u')
		return (ft_putnbase(va_arg(args, unsigned int), \
		"0123456789", fd));
	else if (flag == 'x')
		return (ft_putnbase(va_arg(args, unsigned int), \
		"0123456789abcdef", fd));
	else if (flag == 'X')
		return (ft_putnbase(va_arg(args, unsigned int), \
		"0123456789ABCDEF", fd));
	else if (flag == 'p')
		return (ft_print_address(va_arg(args, unsigned long long), fd));
	else if (flag == '%')
		return (ft_print_percent());
	else
		return (0);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		len;
	int		fd;

	len = 0;
	i = 0;
	fd = 1;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_formats(args, str[i], fd);
		}
		else
		{
			ft_print_char(str[i], fd);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:48:35 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/20 16:48:58 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	y;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		y = (unsigned int)(n * -1);
	}
	else
		y = (unsigned int)n;
	if (y >= 10)
		ft_putnbr_fd((y / 10), fd);
	ft_putchar_fd((char)(y % 10 + 48), fd);
}

/*int main()
{
	ft_putnbr_fd(4, 1);
	return 0;
}*/
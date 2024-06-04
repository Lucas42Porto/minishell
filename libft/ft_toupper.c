/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:29:44 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/20 16:44:19 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 'a') && (c <= 'z'))
		c -= ('a' - 'A');
	return (c);
}

// int		main(void)
// {
// 	printf("%d\n", ft_toupper(r));
// 	printf("%d\n", toupper(r));

// 	return (0);
// }
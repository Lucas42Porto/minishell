/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:37:47 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/14 17:49:13 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s && s[len] != c && s[len])
		len++;
	return (len);
}

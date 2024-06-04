/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:02:33 by lumarque          #+#    #+#             */
/*   Updated: 2023/07/01 17:03:52 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	while (n--)
		*pdest++ = *psrc++;
	return (dest);
}

size_t	strlen_at(const char *str, int avoid)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != avoid)
		i++;
	return (i);
}

char	*find_chr(const char *buffer, int to_find)
{
	if (!buffer)
		return (NULL);
	while (*buffer)
	{
		if (*(unsigned char *)buffer == (unsigned char)to_find)
			return ((char *)buffer);
		buffer++;
	}
	if (*(unsigned char *)buffer == (unsigned char)to_find)
		return ((char *)buffer);
	return (NULL);
}

char	*cpy_buffer(const char *buffer, size_t len)
{
	char	*cpy;
	size_t	i;

	cpy = (char *) malloc(len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (buffer[i] && i < len)
	{
		cpy[i] = buffer[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*to_join(char *previous, const char *current)
{
	size_t	len_prev;
	size_t	len_curr;
	char	*tmp;

	len_prev = 0;
	len_curr = 0;
	if (previous)
		len_prev = strlen_at(previous, '\0');
	len_curr = strlen_at(current, '\0');
	tmp = (char *)malloc(len_prev + len_curr + 1);
	if (!tmp)
		return (NULL);
	if (previous)
		ft_memcpy(tmp, previous, len_prev);
	ft_memcpy(tmp + len_prev, current, len_curr);
	tmp[len_prev + len_curr] = '\0';
	if (previous)
		free(previous);
	return (tmp);
}

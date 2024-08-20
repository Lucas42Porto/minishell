/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:54:40 by resilva           #+#    #+#             */
/*   Updated: 2024/08/20 21:45:49 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Se o novo tamanho for 0, apenas libera a memória original e retorna NULL.
Aloca memória para o novo tamanho.
Se o ponteiro original era NULL, retorna o ponteiro para o novo bloco.
Copia os dados do bloco original para o novo bloco, até o tamanho mínimo 
entre old_size e new_size.*/
#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

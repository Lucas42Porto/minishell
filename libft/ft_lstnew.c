/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:44:38 by lumarque          #+#    #+#             */
/*   Updated: 2023/05/08 20:02:56 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*e;

	e = (t_list *)malloc(sizeof(t_list));
	if (!e)
		return (NULL);
	e->content = content;
	e->next = NULL;
	return (e);
}

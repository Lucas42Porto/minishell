/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:07:23 by lumarque          #+#    #+#             */
/*   Updated: 2023/05/08 20:02:48 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*alst;
	t_list	*e;

	if (!lst)
		return (NULL);
	alst = ft_lstnew(f(lst->content));
	if (!alst)
		return (NULL);
	e = alst;
	while (lst->next)
	{
		lst = lst->next;
		e->next = ft_lstnew((f)(lst->content));
		if (!e->next)
		{
			ft_lstclear(&alst, del);
			return (NULL);
		}
		e = e->next;
	}
	return (alst);
}

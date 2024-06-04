/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:03 by lumarque          #+#    #+#             */
/*   Updated: 2023/05/08 20:02:40 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

/*
void	ft_print_result(t_list *elem)
{
	int		len;

	len = 0;
	while (((char *)elem->content)[len])
		len++;
	write(1, elem->content, len);
	write(1, "\n", 1);
}

int main(int argc, const char *argv[])
{
	t_list		*begin;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;

	elem = ft_lstnew("test");
	elem2 = ft_lstnew("link");
	elem3 = ft_lstnew("list");
	elem4 = ft_lstnew("libft");
	if (!elem || !elem2 || !elem3 || !elem4)
		return (0);
	else
	{
		begin = NULL;
		ft_lstadd_back(&begin, elem4);
		ft_lstadd_back(&begin, elem3);
		ft_lstadd_back(&begin, elem2);
		ft_lstadd_back(&begin, elem);

		ft_print_result(ft_lstlast(begin));
	}
	return (0);
}
*/
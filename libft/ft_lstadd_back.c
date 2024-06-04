/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:53:21 by lumarque          #+#    #+#             */
/*   Updated: 2023/05/08 20:01:59 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	ft_print_result(t_list *elem)
{
	int		len;

	len = 0;
	while (((char *)elem->content)[len])
		len++;
	write(1, elem->content, len);
	write(1, "\n", 1);
}

int main()
{
	t_list		*begin;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("test");
	char		*str2 = strdup("link");
	char		*str3 = strdup("list");
	char		*str4 = strdup("libft");

	elem = ft_lstnew(str);
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);
	elem4 = ft_lstnew(str4);
	if (!elem || !elem2 || !elem3 || !elem4)
		return (0);
	else
	{
		begin = NULL;
		ft_lstadd_back(&begin, elem4);
		ft_lstadd_back(&begin, elem3);
		ft_lstadd_back(&begin, elem2);
		ft_lstadd_back(&begin, elem);
		while (begin)
		{
			ft_print_result(begin);
			begin = begin->next;
		}
	}
	return (0);
}*/
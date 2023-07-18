/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:55:30 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/09 15:00:28 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iter;
	t_list	*ptr;

	if (!lst)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		iter = ptr->next;
		f(ptr->content);
		ptr = iter;
	}
}

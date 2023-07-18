/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:05:47 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/09 11:30:58 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*ptr;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		temp = (ptr)->next;
		ft_lstdelone(ptr, del);
		ptr = temp;
	}
	*lst = NULL;
}

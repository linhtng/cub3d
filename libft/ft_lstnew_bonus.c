/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:38:45 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/08 17:42:20 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlink;

	newlink = (t_list *) malloc(sizeof(t_list));
	if (newlink)
	{
		newlink->content = content;
		newlink->next = NULL;
	}
	else
		return (NULL);
	return (newlink);
}

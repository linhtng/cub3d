/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:37:58 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/10 14:26:55 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	len;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	len = count * size;
	if (len / size != count)
		return (NULL);
	p = (void *) malloc (len);
	if (p == 0)
		return (p);
	ft_bzero(p, len);
	return (p);
}

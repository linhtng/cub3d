/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:49:53 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/01 14:00:16 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	remain_size;
	size_t	slen;

	remain_size = dstsize;
	slen = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (slen);
	while (*dst != '\0' && remain_size > 0)
	{
		dst++;
		remain_size--;
	}
	dlen = dstsize - remain_size;
	if (remain_size > 1)
		ft_strlcpy(dst, src, remain_size);
	return (dlen + slen);
}

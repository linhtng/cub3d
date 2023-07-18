/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:48:11 by thuynguy          #+#    #+#             */
/*   Updated: 2022/10/26 12:53:06 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	n;

	n = 0;
	if (dstsize > 0)
	{
		while ((dstsize - 1) > 0 && src[n] != '\0')
		{
			dst[n] = src[n];
			n++;
			dstsize--;
		}
		dst[n] = '\0';
	}
	n = ft_strlen(src);
	return (n);
}

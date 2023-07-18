/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:31:05 by thuynguy          #+#    #+#             */
/*   Updated: 2022/07/07 14:44:53 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;
	char	*ptr;

	i = ft_strlen(src);
	str = (char *) malloc(sizeof(*src) * (i + 1));
	if (!str)
		return (NULL);
	ptr = str;
	ft_memmove(ptr, src, i);
	ptr[i] = '\0';
	return (str);
}

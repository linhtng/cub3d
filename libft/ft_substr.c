/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:32:29 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/01 18:55:58 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*p;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else
	{
		if (len > (ft_strlen(s) - start))
			len = ft_strlen(s) - start;
		sub = (char *) malloc(sizeof(char) * len + 1);
		if (!sub)
			return (NULL);
		p = sub;
		ft_strlcpy(p, s + start, len + 1);
	}
	return (sub);
}

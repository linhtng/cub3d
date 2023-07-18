/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:52:39 by thuynguy          #+#    #+#             */
/*   Updated: 2022/10/29 14:33:50 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && len >= ft_strlen(needle))
	{
		j = 0;
		while (str[i + j] != '\0' && (i + j) < len && str[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

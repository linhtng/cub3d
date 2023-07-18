/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:19:27 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/05 18:34:14 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*map;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	map = (char *) malloc(sizeof(char) * (len + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < len)
	{
		map[i] = f(i, s[i]);
		i++;
	}
	map[i] = '\0';
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:28:29 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/03 15:48:45 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ltrim_nr(char const *s1, char const *set)
{
	char const	*newleft;
	int			ltrim_nr;

	newleft = s1;
	ltrim_nr = 0;
	while (ft_strchr(set, *newleft) != NULL)
	{
		newleft++;
		ltrim_nr++;
	}
	return (ltrim_nr);
}

static int	rtrim_nr(char const *s1, char const *set)
{
	char const	*newright;
	int			rtrim_nr;

	newright = s1 + ft_strlen(s1) - 1;
	rtrim_nr = 0;
	while (newright != s1 && ft_strchr(set, *newright) != NULL)
	{
		newright--;
		rtrim_nr++;
	}
	return (rtrim_nr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	int		r;
	int		lenres;
	char	*res;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (ft_strchr(set, s1[i]) != NULL)
	{
		i++;
		if (s1[i] == '\0')
			return (ft_strdup(""));
	}
	l = ltrim_nr(s1, set);
	r = rtrim_nr(s1, set);
	lenres = ft_strlen(s1) - l - r;
	res = ft_substr(s1, l, lenres);
	return (res);
}

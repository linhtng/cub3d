/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:24:40 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/16 16:45:01 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}
	return (count);
}

void	*ft_gnl_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src && dst < (src + len))
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_gnl_strjoin(char *s1, char const *s2, int len)
{
	int		len1;
	int		ret;
	char	*res;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_gnl_strdup(s2));
	len1 = ft_gnl_strlen(s1);
	ret = len1 + len;
	if (ret == 0)
		return (NULL);
	res = (char *) malloc(sizeof(*s1) * (ret + 1));
	if (!res)
		return (NULL);
	ft_gnl_memmove(res, s1, len1);
	ft_gnl_memmove(&res[len1], s2, len);
	res[ret] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*ft_gnl_strdup(const char *src)
{
	int		i;
	char	*str;
	char	*ptr;

	i = ft_gnl_strlen(src);
	str = (char *) malloc(sizeof(*src) * (i + 1));
	if (!str)
		return (NULL);
	ptr = str;
	ft_gnl_memmove(ptr, src, i);
	ptr[i] = '\0';
	return (str);
}

char	*ft_gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*p;
	size_t	slen;

	slen = ft_gnl_strlen(s);
	if (!s || start >= slen)
		return (NULL);
	else
	{
		if (len > (slen - start))
			len = slen - start;
		sub = (char *) malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		p = sub;
		ft_gnl_memmove(p, s + start, len);
		p[len] = '\0';
	}
	return (sub);
}

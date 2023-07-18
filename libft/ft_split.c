/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:08:00 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/14 13:00:52 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	word_count(char const *s, char const c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
			i = 0;
		if (*s != c && i == 0)
		{
			count++;
			i = 1;
		}
		s++;
	}
	return (count);
}

static char	**make_arr(char const*s, char c)
{
	char	**res;
	int		len;

	if (!s)
		return (NULL);
	len = word_count(s, c);
	res = (char **) malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = NULL;
	return (res);
}

static int	free_arr(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		arr[i] = NULL;
		free(arr[i]);
		i++;
	}
	arr = NULL;
	free(arr);
	return (0);
}

static int	do_split(char **arr, char const *s, char c)
{
	size_t		i;
	int			j;
	int			word_start;
	size_t		slen;

	i = 0;
	j = 0;
	word_start = -1;
	slen = ft_strlen(s);
	while (i <= slen)
	{
		if (s[i] != '\0' && s[i] != c && word_start < 0)
			word_start = i;
		if ((s[i] == c || i == slen) && word_start >= 0)
		{
			arr[j] = ft_substr(s, word_start, i - word_start);
			if (!arr[j])
				return (free_arr(arr, j));
			j++;
			word_start = -1;
		}
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	int			elem;

	arr = make_arr(s, c);
	if (!arr)
		return (NULL);
	elem = do_split(arr, s, c);
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:04:53 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/05 17:45:09 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	chr_count(int n)
{
	int	res;

	res = 0;
	if (n < 0)
		res = 1;
	while (n != 0)
	{
		n = n / 10;
		res++;
	}
	return (res);
}

static void	reverse_str(char *str)
{
	char	*start;
	char	*end;
	char	temp;

	start = str;
	if (*str == '-')
		start++;
	end = str + ft_strlen(str) - 1;
	while (end > start)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

static void	negative_itoa(char *ret, int n)
{
	size_t	i;

	i = 1;
	ret[0] = '-';
	while (n != 0)
	{
		ret[i] = n % 10 * (-1) + '0';
		n = n / 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	ret = (char *) malloc(sizeof(char) * (chr_count(n) + 1));
	if (!ret)
		return (NULL);
	ret[chr_count(n)] = '\0';
	if (n < 0)
		negative_itoa(ret, n);
	else if (n > 0)
	{
		i = 0;
		while (n != 0)
		{
			ret[i] = n % 10 + '0';
			n = n / 10;
			i++;
		}
	}
	reverse_str(ret);
	return (ret);
}

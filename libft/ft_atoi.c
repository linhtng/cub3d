/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:49:58 by thuynguy          #+#    #+#             */
/*   Updated: 2022/10/29 15:50:27 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (-1);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			break ;
		result = result * 10 + *str - '0';
		str++;
	}
	if (*str && ft_isspace(*str))
	{
		while (ft_isspace(*str))
			str++;
	}
	if (!*str)
		return (result);
	else
		return (-1);
}

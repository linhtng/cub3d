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
static int	overflow(long result, int sign)
{
	int	overflow_res;

	overflow_res = 1;
	if ((result * sign) > 2147483648)
		overflow_res = -1;
	if ((result * sign) < -2147483648)
		overflow_res = 0;
	return (overflow_res);
}

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int		digit_nr;
	long	result;
	int		sign;

	digit_nr = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && digit_nr < 10)
	{
		result = result * 10 + *str - '0';
		digit_nr++;
		str++;
	}
	if (overflow(result, sign) != 1)
		result = overflow(result, sign);
	return (result * sign);
}

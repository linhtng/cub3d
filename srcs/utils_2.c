/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:42:17 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/05 19:44:11 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"

float	correct_degrees(float degrees)
{
	if (degrees < 0)
		degrees += 360;
	else if (degrees >= 360)
		degrees -= 360;
	return (degrees);
}
float	deg_to_rad(float degrees)
{
	float	radians;

	radians  = degrees * (M_PI / 180);
	return (radians);
}
int		ft_abs(int val)
{
	if (val < 0)
		return (val * -1);
	return (val);
}

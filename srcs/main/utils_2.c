/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:42:17 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 16:45:29 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

	radians = degrees * (M_PI / 180);
	return (radians);
}

float	get_distance(t_vector *player, t_vector *wall_hit)
{
	float	a;
	float	b;
	float	c;

	a = player->x - wall_hit->x;
	b = player->y - wall_hit->y;
	c = sqrt((a * a) + (b * b));
	return (c);
}

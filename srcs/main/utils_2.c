/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:42:17 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 15:56:51 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * correct_degrees() corrects the float degrees to be between 0 and 360.
 */
float	correct_degrees(float degrees)
{
	if (degrees < 0)
		degrees += 360;
	else if (degrees >= 360)
		degrees -= 360;
	return (degrees);
}

/*
 * deg_to_rad() converts the float degrees to radians.
 */
float	deg_to_rad(float degrees)
{
	float	radians;

	radians = degrees * (M_PI / 180);
	return (radians);
}

/*
 * get_distance() returns the distance between the t_vecotrs player and 
 * wall_hit using the Pythagorean theorem.
 */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:42:17 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/31 18:02:04 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * correct_degrees() corrects the double degrees to be between 0 and 360.
 */
double	correct_degrees(double degrees)
{
	if (degrees < 0)
		degrees += 360;
	else if (degrees >= 360)
		degrees -= 360;
	return (degrees);
}

/*
 * deg_to_rad() converts the double degrees to radians.
 */
double	deg_to_rad(double degrees)
{
	double	radians;

	radians = degrees * (M_PI / 180);
	return (radians);
}

/*
 * get_distance() returns the distance between the t_vecotrs player and 
 * wall_hit using the Pythagorean theorem.
 */
double	get_distance(t_vector *player, t_vector *wall_hit)
{
	double	a;
	double	b;
	double	c;

	a = player->x - wall_hit->x;
	b = player->y - wall_hit->y;
	c = sqrt((a * a) + (b * b));
	return (c);
}

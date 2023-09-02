/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/09/02 16:03:01 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * identify_wall_direction() identifies the wall direction based on if the
 * shortest distance to the wall was a verical or horizontal hit and the 
 * angle of the ray.
*/
static int	identify_wall_direction(t_ray_calc *ray_info)
{
	if (ray_info->shortest == 'h' && 
		(ray_info->angle >= 0 && ray_info->angle < 180))
		return (SOUTH);
	else if (ray_info->shortest == 'h' && 
		(ray_info->angle >= 180 && ray_info->angle < 360))
		return (NORTH);
	else if (ray_info->shortest == 'v' && 
		(ray_info->angle >= 90 && ray_info->angle < 270))
		return (EAST);
	else if (ray_info->shortest == 'v' && 
		(ray_info->angle >= 270 || ray_info->angle < 90))
		return (WEST);
	return (-1);
}

/*
 * draw_view() identifies the wall direction and calls draw_textured_walls()
 * to draw the wall with the desired texture.
*/
void	draw_view(t_cubed *cubed, t_ray_calc *ray_info, int x)
{
	int	direction;

	direction = identify_wall_direction(ray_info);
	draw_textured_walls(cubed, x, ray_info, direction);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:49:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/20 17:44:33 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
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

	radians  = degrees * (M_PI / 180);
	// printf("DEG: %f, RAD: %f", degrees, radians);//printed with correct values
	return (radians);
}

//TODO: shoot one ray
void	shoot_one_ray_horizontal(t_cubed *cubed, t_scene *scene, float angle)
{
	t_ray_calc ray;

	// scene = (void *) scene;
	//determine direction
	ray.dir_modifier.x = 1;
	if (angle > 90 && angle < 270)
		ray.dir_modifier.x = -1;
	ray.dir_modifier.y = 1;
	if (angle < 180)//changed to be - for 'up'
		ray.dir_modifier.y = -1;
	//find first intersection
	if (ray.dir_modifier.y == 1)
		ray.map_intersection.y = ((cubed->player.location.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE);// should this just be -1?? ****changed to + CS
	else
		ray.map_intersection.y = (cubed->player.location.y / CELL_SIZE) * CELL_SIZE - CELL_SIZE;
	ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;
	ray.y_inc = (cubed->player.location.y - ray.map_intersection.y);//do I want abs value here?/////* ray.dir_modifier.y
	ray.map_intersection.x = cubed->player.location.x + (ray.y_inc / tan(deg_to_rad(angle)));//check about 0 values here
	ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);
	//PRINT to CHECK
	printf("PLAYER LOCATION X,Y: %d,%d\n", cubed->player.location.x, cubed->player.location.y);
	printf("FIRST INTERSECTION:\n");
	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
	printf("MODIFIERS X: %i, Y: %i\n", ray.dir_modifier.x, ray.dir_modifier.y);
	cubed->player.location.color = 0xFFFFFF;
	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);
	//TODO:save distances

	//find second intersection// repeat till grid == wall
	while (ray.map_intersection.y < CELL_SIZE * scene->lines && ray.map_intersection.y > 0)
	{	
	ray.y_inc = CELL_SIZE * ray.dir_modifier.y;
	ray.x_inc = (ft_abs(CELL_SIZE / tan(deg_to_rad(angle)))) * ray.dir_modifier.x;//check for 0 vals
	ray.map_intersection.y += ray.y_inc;
	ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;
	ray.map_intersection.x += ray.x_inc;
	ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);
	//PRINT to CHECK
	printf("NEXT INTERSECTION:\n");
	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
	// cubed->player.location.color = 0x999911;
	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);
	}
}

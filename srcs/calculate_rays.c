/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:49:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/26 17:48:56 by jebouche         ###   ########.fr       */
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
void	shoot_one_ray_horizontal(t_cubed *cubed, t_scene *scene, float angle)
{
	t_ray_calc ray;

	ray.angle = angle;
	ray.dof = 0;
	ray.cotan = 1.0 / tan(deg_to_rad(ray.angle));//or cotan???
	if (sin(deg_to_rad(ray.angle)) > 0.001) //looking down ray.angle > 180
	{
		ray.map.y = ((int)cubed->player.location.y / CELL_SIZE) * CELL_SIZE - 0.00001;
		ray.map.x = cubed->player.location.x + ((cubed->player.location.y - ray.map.y) * ray.cotan);
		ray.hd.y = -CELL_SIZE;
		ray.hd.x = -ray.hd.y * ray.cotan;
	}
	else if (sin(deg_to_rad(ray.angle)) < -0.001) //looking up ray.angle < 180
	{
		ray.map.y = ((int)cubed->player.location.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
		ray.map.x = cubed->player.location.x + ((cubed->player.location.y - ray.map.y) * ray.cotan);
		ray.hd.y = CELL_SIZE;
		ray.hd.x = -ray.hd.y * ray.cotan;		
	}
	else //will not hit a horizontal if (ray.angle == 0 || ray.angle == 180)
	{
		ray.map.x = cubed->player.location.x;
		ray.map.y = cubed->player.location.y;
		ray.dof = 8;
	}
	//check hit wall
	while (ray.dof < MAX_DOF)
	{
		ray.grid.x = (int)ray.map.x / CELL_SIZE;
		ray.grid.y = (int)ray.map.y / CELL_SIZE;
		printf("GRID XY: %f, %f DOF: %i\n", ray.grid.x, ray.grid.y, ray.dof);
		if (ray.grid.y >= 0 && (ray.grid.x < scene->columns && ray.grid.y < scene->lines && scene->map[(int)ray.grid.y][(int)ray.grid.x] == '1')) //(ray.grid.x < 0 || ray.grid.y < 0 || ray.grid.x > scene->columns || ray.grid.y < scene->lines)
			ray.dof = 8;
		else
		{
			ray.map.x += ray.hd.x;
			ray.map.y += ray.hd.y;
			(ray.dof)++;
		}
	}
	cubed->player.location.color = 0xFFFFFF;//
	ft_bresenham(cubed->player.location, ray.map, cubed->player_img);//
}



void	shoot_one_ray_vertical(t_cubed *cubed, t_scene *scene, float angle)
{
	scene = (void *) scene;
	t_ray_calc ray;

	ray.angle = angle;
	ray.dof = 0;
	ray.tan = tan(deg_to_rad(ray.angle));
	if (cos(deg_to_rad(ray.angle)) < -0.001) //looking left?
	{
		ray.map.x = ((int)cubed->player.location.x / CELL_SIZE) * CELL_SIZE - 0.00001;
		ray.map.y = cubed->player.location.y + ((cubed->player.location.x - ray.map.x) * ray.tan);
		ray.vd.x = -CELL_SIZE;
		ray.vd.y = -ray.vd.x * ray.tan;
	}
	else if (cos(deg_to_rad(ray.angle)) > 0.001) //looking right?
	{
		ray.map.x = ((int)cubed->player.location.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
		ray.map.y = cubed->player.location.y + ((cubed->player.location.x - ray.map.x) * ray.tan);
		ray.vd.x = CELL_SIZE;
		ray.vd.y = -ray.vd.x * ray.tan;		
	}
	else //will not hit a horizontal if (ray.angle == 0 || ray.angle == 180)
	{
		ray.map.x = cubed->player.location.x;
		ray.map.y = cubed->player.location.y;
		ray.dof = MAX_DOF;
	}
	//check hit wall
	while (ray.dof < MAX_DOF)
	{
		ray.grid.x = (int)ray.map.x / CELL_SIZE;
		ray.grid.y = (int)ray.map.y / CELL_SIZE;
		printf("GRID XY: %f, %f DOF: %i\n", ray.grid.x, ray.grid.y, ray.dof);
	
		if (ray.grid.y >= 0  && ray.grid.x  >= 0 && ray.grid.x < scene->columns && ray.grid.y < scene->lines && scene->map[(int)ray.grid.y][(int)ray.grid.x] == '1')
			ray.dof = MAX_DOF;
		else
		{
			ray.map.x += ray.vd.x;
			ray.map.y += ray.vd.y;
			(ray.dof)++;
		}
	}
	cubed->player.location.color = 0x000FFF;//
	ft_bresenham(cubed->player.location, ray.map, cubed->player_img);//
}

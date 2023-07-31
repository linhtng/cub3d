/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:49:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/31 14:40:05 by jebouche         ###   ########.fr       */
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
	return (radians);
}

void	check_hit_wall(t_cubed *cubed, t_vector *grid, t_vector *map, t_vector *offset)
{
	int dof;

	dof = 0;
	while (dof < MAX_DOF)
	{
		grid->x = (int)map->x / CELL_SIZE;
		grid->y = (int)map->y / CELL_SIZE;
		if (grid->y >= 0  && grid->x  >= 0 && grid->x < cubed->scene->columns && grid->y < cubed->scene->lines && cubed->scene->map[(int)grid->y][(int)grid->x] == '1')
			dof = MAX_DOF;
		else
		{
			map->x += offset->x;
			map->y += offset->y;
			dof++;
		}
	}
}
void	shoot_one_ray_horizontal(t_cubed *cubed, t_ray_calc *ray)
{
	ray->cotan = 1.0 / tan(deg_to_rad(ray->angle));//or cotan???
	if (sin(deg_to_rad(ray->angle)) > 0.001) //looking down ray.angle > 180
	{
		ray->h_map.y = ((int)cubed->player.location.y / CELL_SIZE) * CELL_SIZE - 0.00001;
		ray->h_map.x = cubed->player.location.x + ((cubed->player.location.y - ray->h_map.y) * ray->cotan);
		ray->hd.y = -CELL_SIZE;
		ray->hd.x = -ray->hd.y * ray->cotan;
	}
	else if (sin(deg_to_rad(ray->angle)) < -0.001) //looking up ray.angle < 180
	{
		ray->h_map.y = ((int)cubed->player.location.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
		ray->h_map.x = cubed->player.location.x + ((cubed->player.location.y - ray->h_map.y) * ray->cotan);
		ray->hd.y = CELL_SIZE;
		ray->hd.x = -ray->hd.y * ray->cotan;		
	}
	else //will not hit a horizontal if (ray.angle == 0 || ray.angle == 180)
	{
		ray->h_map.x = cubed->player.location.x;
		ray->h_map.y = cubed->player.location.y;
		ray->dof = MAX_DOF;
	}
	//don't do check hit wall if MAX_DOF set?
	check_hit_wall(cubed, &ray->h_grid, &ray->h_map, &ray->hd);
}

void	shoot_one_ray_vertical(t_cubed *cubed, t_ray_calc *ray)
{
	ray->tan = tan(deg_to_rad(ray->angle));
	if (cos(deg_to_rad(ray->angle)) < -0.001) //looking left?
	{
		ray->v_map.x = ((int)cubed->player.location.x / CELL_SIZE) * CELL_SIZE - 0.00001;
		ray->v_map.y = cubed->player.location.y + ((cubed->player.location.x - ray->v_map.x) * ray->tan);
		ray->vd.x = -CELL_SIZE;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else if (cos(deg_to_rad(ray->angle)) > 0.001) //looking right?
	{
		ray->v_map.x = ((int)cubed->player.location.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
		ray->v_map.y = cubed->player.location.y + ((cubed->player.location.x - ray->v_map.x) * ray->tan);
		ray->vd.x = CELL_SIZE;
		ray->vd.y = -ray->vd.x * ray->tan;		
	}
	else //will not hit a horizontal if (ray.angle == 0 || ray.angle == 180)
	{
		ray->v_map.x = cubed->player.location.x;
		ray->v_map.y = cubed->player.location.y;
		ray->dof = MAX_DOF;
	}
	//don't do check hit wall if MAX_DOF set?
	check_hit_wall(cubed, &ray->v_grid, &ray->v_map, &ray->vd);
}

float	get_distance(t_vector *player, t_vector *wall_hit)
{
	float a;
	float b;
	float c;

	a = player->x - wall_hit->x;
	b = player->y - wall_hit->y;
	c = sqrt((a * a) + (b * b));
	return (c);
}
void	cast_rays(t_cubed *cubed)
{
	// initialize info
	t_ray_calc ray;
	int		rays_drawn;

	ray.angle = correct_degrees(cubed->player.angle - FOV / 2);
	rays_drawn = 0;
	cubed->player.location.color = 0x000FFF;//
	ft_memset(cubed->raycast_info->r_img->addr, 0x00FFFFFF, PROJECTION_WIDTH * PROJECTION_HEIGHT * (cubed->raycast_info->r_img->bits_per_pixel / 8));//creates transparent
	while ( rays_drawn < PROJECTION_WIDTH ) //
	{
		printf("CAST A RAY!\n");
		shoot_one_ray_horizontal(cubed, &ray);//
		shoot_one_ray_vertical(cubed, &ray);//
		//get shortest
		ray.h_distance = get_distance(&cubed->player.location, &ray.h_map);
		ray.v_distance = get_distance(&cubed->player.location, &ray.v_map);
		if (ray.h_distance < ray.v_distance)
		{
			ft_bresenham(cubed->player.location, ray.h_map, cubed->player_img);////draw h
			draw_view(cubed, ray.h_distance, PROJECTION_WIDTH - rays_drawn, 'h');
		}
		else
		{
			ft_bresenham(cubed->player.location, ray.v_map, cubed->player_img);////draw v
			draw_view(cubed, ray.v_distance, PROJECTION_WIDTH - rays_drawn, 'v');
		}
		
		printf("HORIZONTAL DISTANCE: %f\n", get_distance(&cubed->player.location, &ray.h_map));
		printf("VERTICAL DISTANCE: %f\n", get_distance(&cubed->player.location, &ray.v_map));
		//use that to draw on map
		//do next ray
		ray.angle += cubed->raycast_info->angle_between_rays;
		rays_drawn++;
	}
}

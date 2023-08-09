/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:49:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 11:40:12 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

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
	ray->cotan = 1.0 / tan(deg_to_rad(ray->angle));
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
	}
	check_hit_wall(cubed, &ray->h_grid, &ray->h_map, &ray->hd);
}

void	shoot_one_ray_vertical(t_cubed *cubed, t_ray_calc *ray)
{
	ray->tan = tan(deg_to_rad(ray->angle));
	if (cos(deg_to_rad(ray->angle)) < -0.001) //looking left
	{
		ray->v_map.x = ((int)cubed->player.location.x / CELL_SIZE) * CELL_SIZE - 0.00001;
		ray->v_map.y = cubed->player.location.y + ((cubed->player.location.x - ray->v_map.x) * ray->tan);
		ray->vd.x = -CELL_SIZE;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else if (cos(deg_to_rad(ray->angle)) > 0.001) //looking right
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
	}
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
	t_ray_calc ray;
	int		rays_drawn;

	ray.angle = correct_degrees(cubed->player.angle - FOV / 2);
	rays_drawn = 0;
	while ( rays_drawn <= PROJECTION_WIDTH ) //
	{
		shoot_one_ray_horizontal(cubed, &ray);//
		shoot_one_ray_vertical(cubed, &ray);//
		ray.h_distance = get_distance(&cubed->player.location, &ray.h_map);
		ray.v_distance = get_distance(&cubed->player.location, &ray.v_map);
		if (ray.h_distance < ray.v_distance)
		{
			ft_bresenham(cubed->player.location, ray.h_map, cubed->player_img);////draw h
			draw_view(cubed, ray.h_distance * cos(deg_to_rad(ray.angle - cubed->player.angle)), PROJECTION_WIDTH - rays_drawn, 'h');
		}
		else
		{
			ft_bresenham(cubed->player.location, ray.v_map, cubed->player_img);////draw v
			draw_view(cubed, ray.v_distance * cos(deg_to_rad(ray.angle - cubed->player.angle)), PROJECTION_WIDTH - rays_drawn, 'v');
		}
		ray.angle += cubed->raycast_info->angle_between_rays;
		rays_drawn++;
	}
}

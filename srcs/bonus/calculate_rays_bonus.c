/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:49:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 20:29:44 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_hit_wall(t_cubed *cubed, t_vector *grid, t_vector *map, \
t_vector *offset)
{
	int	dof;

	dof = 0;
	if (map->x == cubed->scene->player.location.x && \
	map->y == cubed->scene->player.location.x)
		return ;
	while (dof < MAX_DOF)
	{
		grid->x = (int)map->x / CELL_SIZE;
		grid->y = (int)map->y / CELL_SIZE;
		if (grid->y >= 0 && grid->x >= 0 && grid->x < cubed->scene->map.width \
			&& grid->y < cubed->scene->map.height && ft_strchr(HITABLE_MAP_VAL, \
			cubed->scene->map.grid[(int)grid->y][(int)grid->x]))
		{
			dof = MAX_DOF;
		}
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
	ray->cotan = 1.0f / tan(deg_to_rad(ray->angle));
	if (sin(deg_to_rad(ray->angle)) > 0.001f)
	{
		ray->h_map.y = ((int)cubed->scene->player.location.y / CELL_SIZE) * \
		CELL_SIZE - 0.0001f;
		ray->h_map.x = cubed->scene->player.location.x + \
		((cubed->scene->player.location.y - ray->h_map.y) * ray->cotan);
		ray->hd.y = (float)-CELL_SIZE;
		ray->hd.x = -ray->hd.y * ray->cotan;
	}
	else if (sin(deg_to_rad(ray->angle)) < -0.001)
	{
		ray->h_map.y = (int)cubed->scene->player.location.y / CELL_SIZE * \
		CELL_SIZE + CELL_SIZE;
		ray->h_map.x = cubed->scene->player.location.x + \
		((cubed->scene->player.location.y - ray->h_map.y) * ray->cotan);
		ray->hd.y = (float)CELL_SIZE;
		ray->hd.x = -ray->hd.y * ray->cotan;
	}
	else
	{
		ray->h_map.x = cubed->scene->player.location.x;
		ray->h_map.y = cubed->scene->player.location.y;
	}
	check_hit_wall(cubed, &ray->h_grid, &ray->h_map, &ray->hd);
}

void	shoot_one_ray_vertical(t_cubed *cubed, t_ray_calc *ray)
{
	ray->tan = tan(deg_to_rad(ray->angle));
	if (cos(deg_to_rad(ray->angle)) < -0.001)
	{
		ray->v_map.x = ((int)cubed->scene->player.location.x / CELL_SIZE) * \
		CELL_SIZE - 0.0001;
		ray->v_map.y = cubed->scene->player.location.y + \
		((cubed->scene->player.location.x - ray->v_map.x) * ray->tan);
		ray->vd.x = -CELL_SIZE;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else if (cos(deg_to_rad(ray->angle)) > 0.001)
	{
		ray->v_map.x = ((int)cubed->scene->player.location.x / CELL_SIZE) * \
		CELL_SIZE + CELL_SIZE;
		ray->v_map.y = cubed->scene->player.location.y + \
		((cubed->scene->player.location.x - ray->v_map.x) * ray->tan);
		ray->vd.x = CELL_SIZE;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else
	{
		ray->v_map.x = cubed->scene->player.location.x;
		ray->v_map.y = cubed->scene->player.location.y;
	}
	check_hit_wall(cubed, &ray->v_grid, &ray->v_map, &ray->vd);
}

void	get_corrected_shortest(t_cubed *cubed, t_ray_calc *ray_info)
{
	float	h_distance;
	float	v_distance;

	h_distance = get_distance(&cubed->scene->player.location, &ray_info->h_map);
	v_distance = get_distance(&cubed->scene->player.location, &ray_info->v_map);
	if (h_distance != 0.0f && (h_distance < v_distance || v_distance == 0.0f))
	{
		ray_info->shortest = 'h';
		ray_info->distance = h_distance * \
		cos(deg_to_rad(ray_info->angle - cubed->scene->player.angle));
	}
	else
	{
		ray_info->shortest = 'v';
		ray_info->distance = v_distance * \
		cos(deg_to_rad(ray_info->angle - cubed->scene->player.angle));
	}
}

void	cast_rays(t_cubed *cubed)
{
	t_ray_calc	ray;
	int			rays_drawn;

	ray.angle = correct_degrees(cubed->scene->player.angle - FOV / 2);
	rays_drawn = 0;
	while (rays_drawn <= PROJECTION_WIDTH)
	{
		shoot_one_ray_horizontal(cubed, &ray);
		shoot_one_ray_vertical(cubed, &ray);
		get_corrected_shortest(cubed, &ray);
		draw_view(cubed, &ray, PROJECTION_WIDTH - rays_drawn);
		ray.angle = \
		correct_degrees(ray.angle + cubed->raycast_info->angle_between_rays);
		rays_drawn++;
	}
}

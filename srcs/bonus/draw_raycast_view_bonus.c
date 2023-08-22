/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 22:05:30 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_floor_ceiling(t_cubed *cubed, float ray_angle, t_draw_info *d_info)
{
	float		delta_y;
	float		ray_fix;

	ray_fix = correct_degrees(cubed->scene->player.angle - ray_angle);
	ray_fix = cos(deg_to_rad(ray_fix));
	d_info->project_y = PROJECTION_HEIGHT;
	while (d_info->project_y >= d_info->floor_start)
	{
		delta_y = d_info->project_y - PROJECTION_HEIGHT / 2;
		d_info->tex.x = (cubed->scene->player.location.x + \
		cos(deg_to_rad(ray_angle)) * 370 * TEXTURE_SIZE / delta_y / ray_fix);
		d_info->tex.y = (cubed->scene->player.location.y - \
		sin(deg_to_rad(ray_angle)) * 370 * TEXTURE_SIZE / delta_y / ray_fix);
		d_info->tex.color = ft_pixel_get(cubed->scene->texture[0], \
		(int)d_info->tex.x & 63, (int)d_info->tex.y & 63);//choose floor texture here
		ft_pixel_put(cubed->raycast_info->r_img, d_info->project_x, \
		d_info->project_y, d_info->tex.color);
		d_info->tex.color = ft_pixel_get(cubed->scene->texture[1], \
		(int)d_info->tex.x & 63, (int)d_info->tex.y & 63);//choose ceiling texture here
		ft_pixel_put(cubed->raycast_info->r_img, d_info->project_x, \
		PROJECTION_HEIGHT - d_info->project_y, d_info->tex.color);
		d_info->project_y--;
	}
}

int	identify_wall_direction(t_ray_calc *ray_info)
{
	if (ray_info->shortest == 'h' && \
	(ray_info->angle >= 0 && ray_info->angle < 180))
		return (SOUTH);
	else if (ray_info->shortest == 'h' && \
	(ray_info->angle >= 180 && ray_info->angle < 360))
		return (NORTH);
	else if (ray_info->shortest == 'v' && \
	(ray_info->angle >= 90 && ray_info->angle < 270))
		return (EAST);
	else if (ray_info->shortest == 'v' && \
	(ray_info->angle >= 270 || ray_info->angle < 90))
		return (WEST);
	return (-1);
}
void	draw_object(t_cubed *cubed, t_ray_calc *ray_info, int x)
{
	//how big to draw the object
	//get what color to draw from the texture
	//get initial x value of the texture to draw from based on draw height and y_step
	//scaling object size
	t_draw_info	draw_info;

	draw_info.height = CELL_SIZE * PROJECTION_HEIGHT / cubed->reward.distance;
	
}

void	draw_view(t_cubed *cubed, t_ray_calc *ray_info, int x)
{
	t_draw_info	draw_info;

	draw_minimap_rays((t_cubed_bonus *)cubed, ray_info);
	draw_info.dir = identify_wall_direction(ray_info);
	draw_info.height = CELL_SIZE * PROJECTION_HEIGHT / ray_info->distance;
	draw_info.project_x = x;
	draw_info.floor_start = cubed->raycast_info->center_of_projection.y - \
	draw_info.height / 2 + draw_info.height;
	b_draw_textured_walls(cubed, ray_info, &draw_info);
	if (draw_info.height < PROJECTION_HEIGHT)
		draw_floor_ceiling(cubed, ray_info->angle, &draw_info);
	if (((t_cubed_bonus *)cubed)->reward.seen)
	{
		printf("[reward distance] %f\n", ((t_cubed_bonus *)cubed)->reward.distance);
		printf("[reward info] grid coor y: %f, x: %f, map_coor: y %f, x %f\n", \
	((t_cubed_bonus *)cubed)->reward.grid_coor.y, ((t_cubed_bonus *)cubed)->reward.grid_coor.x, \
	((t_cubed_bonus *)cubed)->reward.map_coor.y, ((t_cubed_bonus *)cubed)->reward.map_coor.x);
	}
}

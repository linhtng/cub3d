/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 16:07:10 by jebouche         ###   ########.fr       */
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 17:16:32 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * draw_floor_ceiling() draws the floor and ceiling based on the ray angle and
 * the height of the wall. it calculates the delta y and the ray fix to correct
 * the fisheye effect. The texture is chosen based on the ray angle and the
 * delta y. delta_y depends on the project_y that decrements as the loop 
 * iterates.
*/
static void	draw_floor_ceiling(t_cubed *cubed, float ray_angle, \
t_draw_info *d_info)
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
		d_info->tex.color = ft_pixel_get(((t_scene_bonus *)cubed->scene)->\
		bonus_textures[1], (int)d_info->tex.x & 63, (int)d_info->tex.y & 63);
		ft_pixel_put(cubed->raycast_info->r_img, d_info->project_x, \
		d_info->project_y, d_info->tex.color);
		d_info->tex.color = ft_pixel_get(((t_scene_bonus *)cubed->scene)->\
		bonus_textures[2], (int)d_info->tex.x & 63, (int)d_info->tex.y & 63);
		ft_pixel_put(cubed->raycast_info->r_img, d_info->project_x, \
		PROJECTION_HEIGHT - d_info->project_y, d_info->tex.color);
		d_info->project_y--;
	}
}

/*
 * identify_wall_direction() identifies the direction of the wall hit by the
 * raycast. The shortest distance is identified and the angle is checked to
 * determine the direction.
*/
static int	identify_wall_direction(t_ray_calc *ray_info)
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

/*
 * identify_material_hit() identifies the material hit by the raycast is a wall
 * or a door. If the material hit is a door, the DOOR_CLOSED is returned, 
 * otherwise WALL is returned.
*/
static int	identify_material_hit(t_cubed *cubed, t_ray_calc *ray_info)
{
	char	map_char;
	int		y;
	int		x;

	if (ray_info->shortest == 'v')
	{
		x = (int)ray_info->v_grid.x;
		y = (int)ray_info->v_grid.y;
		map_char = cubed->scene->map.grid[y][x];
	}
	else
	{
		x = (int)ray_info->h_grid.x;
		y = (int)ray_info->h_grid.y;
		map_char = cubed->scene->map.grid[y][x];
	}
	if (map_char == DOOR_CLOSED)
		return (DOOR_CLOSED);
	return (WALL);
}

/*
 * draw_view() draws the view of the player based on the raycast information.
 * The direction of the wall is identified and the height of the wall is
 * calculated based on the distance of the wall.
 * The material hit is identified and the appropriate texture is chosen.
 * The floor and ceiling are drawn based on the ray angle and the height 
 * of the wall.
 */
void	draw_view(t_cubed *cubed, t_ray_calc *ray_info, int x)
{
	t_draw_info	draw_info;

	draw_minimap_rays((t_cubed_bonus *)cubed, ray_info);
	draw_info.dir = identify_wall_direction(ray_info);
	draw_info.height = CELL_SIZE * PROJECTION_HEIGHT / ray_info->distance;
	draw_info.project_x = x;
	draw_info.floor_start = cubed->raycast_info->center_of_projection.y - \
	draw_info.height / 2 + draw_info.height;
	draw_info.material_hit = identify_material_hit(cubed, ray_info);
	b_draw_textured_walls(cubed, ray_info, &draw_info);
	if (draw_info.height < PROJECTION_HEIGHT)
		draw_floor_ceiling(cubed, ray_info->angle, &draw_info);
}

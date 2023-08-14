/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/14 11:37:03 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

/* 
	MAP SIZE * PROJECTION WIDTH / DISTANCE OF PLAYER FROM WALL = LINE HEIGHT
	center line height in projection pane ...
 */
void	draw_textured_walls(t_cubed *cubed, float dist, int x, char side)
{
	float		line_height;
	t_vector	start;

	if (side == 'v')
		start.color = 0XFF0000;
	else
		start.color = 0XFFF000;
	line_height = CELL_SIZE * PROJECTION_HEIGHT / dist;
	if (line_height > PROJECTION_HEIGHT)
		line_height = PROJECTION_HEIGHT;
	start.x = x;
	start.y = cubed->raycast_info->center_of_projection.y - line_height / 2;
	// printf("START XY for wall: %f, %f, center of projection %f\n", start.x, start.y, cubed->raycast_info->center_of_projection.y);
	//draw line
	my_put_line_v(cubed->raycast_info->r_img, &start, line_height);
}

void	draw_minimap_rays(t_cubed *cubed, t_ray_calc *ray_info)
{
	if (ray_info->shortest == 'v')
		ft_bresenham(cubed->scene->player.location, ray_info->v_map, cubed->mini_player_img);
	else
		ft_bresenham(cubed->scene->player.location, ray_info->h_map, cubed->mini_player_img);
}

int	identify_wall_direction(t_ray_calc *ray_info)
{
	if (ray_info->shortest == 'h' && (ray_info->angle >= 0 && ray_info->angle < 180))
		return (SOUTH);
	else if (ray_info->shortest == 'h' && (ray_info->angle >= 180 && ray_info->angle < 360))
		return (NORTH);
	else if (ray_info->shortest == 'v' && (ray_info->angle >= 90 && ray_info->angle < 270))
		return (EAST);
	else if (ray_info->shortest == 'v' && (ray_info->angle >= 270 || ray_info->angle < 90))
		return (WEST);
	return (-1);
}

void	draw_view(t_cubed *cubed, t_ray_calc *ray_info, int x)
{
	int	direction;

	draw_minimap_rays(cubed, ray_info);
	//find wall texture NSEW
	direction = identify_wall_direction(ray_info);
	printf("[DIRECTION] %i\n", direction);
	draw_textured_walls(cubed, ray_info->distance, x, ray_info->shortest);
}
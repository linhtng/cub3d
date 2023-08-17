/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 09:28:07 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_raycast_bonus.h"
#include "cub3D_bonus.h"
#include "cub3D.h"
void	draw_minimap_rays(t_cubed *cubed, t_ray_calc *ray_info)
{
	if (ray_info->shortest == 'v')
		ft_bresenham(cubed->scene->player.location, ray_info->v_map, \
		((t_cubed_bonus *)cubed)->mini_player_img);
	else
		ft_bresenham(cubed->scene->player.location, ray_info->h_map, \
		((t_cubed_bonus *)cubed)->mini_player_img);
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
	int	direction;

	draw_minimap_rays(cubed, ray_info);
	direction = identify_wall_direction(ray_info);
	draw_textured_walls(cubed, x, ray_info, direction);
}

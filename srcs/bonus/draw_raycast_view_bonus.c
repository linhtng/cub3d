/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast_view_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:35:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/18 18:01:43 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_minimap_rays(t_cubed_bonus *cubed, t_ray_calc *ray_info)
{
	t_vector mini_player;
	t_vector temp;

	mini_player.x = MINI_MAP_RADIUS;
	mini_player.y = MINI_MAP_RADIUS;
	mini_player.color = 0X99FFFFFF; //60% transparent white
	if (ray_info->shortest == 'v')
	{
		temp.x = ray_info->v_map.x - cubed->scene->player.location.x + MINI_MAP_RADIUS;
		temp.y = ray_info->v_map.y - cubed->scene->player.location.y + MINI_MAP_RADIUS;
		ft_bresenham(mini_player, temp, cubed->mini_player_img);
	}
	else
	{
		temp.x = ray_info->h_map.x - cubed->scene->player.location.x + MINI_MAP_RADIUS;
		temp.y = ray_info->h_map.y - cubed->scene->player.location.y + MINI_MAP_RADIUS;
		ft_bresenham(mini_player, temp, cubed->mini_player_img);
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
	int	direction;

	draw_minimap_rays((t_cubed_bonus *)cubed, ray_info);
	direction = identify_wall_direction(ray_info);
	draw_textured_walls(cubed, x, ray_info, direction);
}

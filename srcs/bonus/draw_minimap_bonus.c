/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 20:32:44 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

void	draw_minimap_rays(t_cubed_bonus *cubed, t_ray_calc *ray_info)
{
	t_vector	mini_player;
	t_vector	temp;

	mini_player.x = MINI_MAP_RADIUS;
	mini_player.y = MINI_MAP_RADIUS;
	mini_player.color = TRANS_WHITE;
	if (ray_info->shortest == 'v')
	{
		temp.x = (((ray_info->v_map.x - cubed->scene->player.location.x) / \
		(float)CELL_SIZE) * MINI_MAP_CELL) + MINI_MAP_RADIUS;
		temp.y = (((ray_info->v_map.y - cubed->scene->player.location.y) / \
		(float)CELL_SIZE) * MINI_MAP_CELL) + MINI_MAP_RADIUS;
		ft_bresenham_clipped(mini_player, temp, cubed->mini_player_img);
	}
	else
	{
		temp.x = (((ray_info->h_map.x - cubed->scene->player.location.x) \
		/ (float)CELL_SIZE) * MINI_MAP_CELL) + MINI_MAP_RADIUS;
		temp.y = (((ray_info->h_map.y - cubed->scene->player.location.y) \
		/ (float)CELL_SIZE) * MINI_MAP_CELL) + MINI_MAP_RADIUS;
		ft_bresenham_clipped(mini_player, temp, cubed->mini_player_img);
	}
}

//TODO color minimap for doors and collectables etc...
unsigned int	get_color(t_map *map, int grid_x, int grid_y)
{
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0 || \
	grid_y >= map->height)
	{
		return (YELLOW);
	}
	else
	{
		if (map->flood[grid_y + 1][grid_x + 1] == FLOODED_WALL)
			return (NAVY_BLUE);
		else if (map->flood[grid_y + 1][grid_x + 1] == BONUS_CHAR)
			return (YELLOW);
		else
			return (PINK);
	}
}

void	put_minimap_pixel(t_cubed_bonus *cubed, t_vector *center, int x, int y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (x - (int)center->x + \
	(cubed->scene->player.location.x / CELL_SIZE) * MINI_MAP_CELL) \
	/ MINI_MAP_CELL;
	grid_y = (y - (int)center->y + \
	(cubed->scene->player.location.y / CELL_SIZE) * MINI_MAP_CELL) \
	/ MINI_MAP_CELL;
	center->color = get_color(&cubed->scene->map, grid_x, grid_y);
	ft_pixel_put(cubed->minimap_img, x, y, center->color);
}

void	draw_filled_circle(t_cubed_bonus *cubed, t_vector *center)
{
	t_vector	image;
	t_vector	delta;
	int			drawn;

	image.y = (int)center->y - MINI_MAP_RADIUS;
	while (image.y <= (int)center->y + MINI_MAP_RADIUS)
	{
		drawn = 0;
		image.x = (int)center->x - MINI_MAP_RADIUS;
		delta.y = image.y - (int)center->y;
		while (image.x < (int)center->x + MINI_MAP_RADIUS)
		{
			delta.x = image.x - (int)center->x;
			if ((int)delta.x * (int)delta.x + (int)delta.y * \
			(int)delta.y <= MINI_MAP_RADIUS * MINI_MAP_RADIUS)
			{
				drawn = 1;
				put_minimap_pixel(cubed, center, image.x, image.y);
			}
			else if (drawn == 1)
				break ;
			image.x++;
		}
		image.y++;
	}
}

void	draw_minimap(t_cubed *cubed)
{
	t_vector	center;

	center.x = MINI_MAP_RADIUS;
	center.y = MINI_MAP_RADIUS;
	center.color = RED;
	draw_filled_circle((t_cubed_bonus *)cubed, &center);
	draw_mini_player(cubed);
}

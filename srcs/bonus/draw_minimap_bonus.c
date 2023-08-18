/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/18 18:15:11 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

unsigned int	get_color(t_map *map, int grid_x, int grid_y)
{
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0 || \
	grid_y >= map->height)
		return (YELLOW);
	else
	{
		if (map->grid[grid_y][grid_x] == '1')
			return (NAVY_BLUE);
		else
			return (PINK);
	}
}

void	put_minimap_pixel(t_cubed_bonus *cubed, t_vector *center, int x, int y)
{
	int	grid_x;
	int grid_y;

	grid_x = (x - (int)center->x  + \
	(int)cubed->scene->player.location.x) / CELL_SIZE;
	grid_y = (y - (int)center->y  + \
	(int)cubed->scene->player.location.y) / CELL_SIZE;
	center->color = get_color(&cubed->scene->map, grid_x, grid_y);
	ft_pixel_put(cubed->minimap_img, x, y, center->color);
}

void	draw_filled_circle(t_cubed_bonus *cubed, t_vector *center)
{
	t_vector image;
	t_vector delta;
	int drawn;

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
	t_vector center;

	center.x = MINI_MAP_RADIUS;
	center.y = MINI_MAP_RADIUS;
	center.color = RED;
	draw_filled_circle((t_cubed_bonus *)cubed, &center);
	draw_mini_player(cubed);
}

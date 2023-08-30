/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 17:08:56 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

/*
 * draw_minimap_rays() draws the cast rays on the minimap. It converts the ray
 * distance to the minimap scall before drawing the line.
*/
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

/*
 * get_color returns the color of the minimap pixel based on the corrosponding
 * grid value. 
 * WALL = NAVY_BLUE
 * FLOOR = PINK
 * DOOR_OPEN = LIGHT_GREY
 * DOOR_CLOSED = DARK_GREY
 * BONUS_CHAR from flooded map = DIM_GREY
 * FLOODED_WALL = NAVY_BLUE
*/
static unsigned int	get_color(t_map *map, int grid_x, int grid_y)
{
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0 || \
	grid_y >= map->height)
	{
		return (DIM_GRAY);
	}
	else
	{
		if (map->flood[grid_y + 1][grid_x + 1] == FLOODED_WALL)
			return (NAVY_BLUE);
		else if (map->flood[grid_y + 1][grid_x + 1] == BONUS_CHAR)
			return (DIM_GRAY);
		else if (map->grid[grid_y][grid_x] == DOOR_OPEN)
			return (LIGHT_GREY);
		else if (map->flood[grid_y + 1][grid_x + 1] == DOOR_CLOSED)
			return (DARK_GREY);
		else
			return (PINK);
	}
}

/*
 * put_minimap_pixel() puts the pixel on the minimap based on the grid location
 * and the player location.
*/
static void	put_minimap_pixel(t_cubed_bonus *cubed, t_vector *center, \
int x, int y)
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

/*
 * draw_circle_minimap() circular minimap based on the set minimap macros
 * using a box bounding method.
*/
static void	draw_circle_minimap(t_cubed_bonus *cubed, t_vector *center)
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

/*
 * draw_minimap() sets the minimap center based on the minmap macros and draws
 * the minimap circle and the player on the minimap.
*/
void	draw_minimap(t_cubed *cubed)
{
	t_vector	center;

	center.x = MINI_MAP_RADIUS;
	center.y = MINI_MAP_RADIUS;
	center.color = RED;
	draw_circle_minimap((t_cubed_bonus *)cubed, &center);
	draw_mini_player(cubed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 17:46:35 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

// TODO move to bonus entire file

// void	draw_circle(t_cubed *cubed, t_vector *center, int x, int y)
// {
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x + x, (int)center->y + y, center->color);
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x - x, (int)center->y + y, center->color);
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x + x, (int)center->y - y, center->color);
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x - x, (int)center->y - y, center->color);
	
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x + y, (int)center->y + x, center->color);
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x - y, (int)center->y + x, center->color);
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x + y, (int)center->y - x, center->color);
// 	ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, (int)center->x - y, (int)center->y - x, center->color);
// }

// void	ft_bresenham_circle(t_cubed *cubed, t_vector *center, int radius)
// {
// 	int	x = 0;
// 	int y = radius;
// 	int decision = 3 - 2 * radius;
// 	draw_circle(cubed, center, x, y);
// 	while ( y >= x)
// 	{
// 		x++;
// 		if (decision > 0)
// 		{
// 			y--;
// 			decision = decision + 4 * (x - y) + 10;
// 		}
// 		else
// 		{
// 			decision = decision + 4 * x + 6;
// 		}
// 		draw_circle(cubed, center, x, y);
// 	}

// }

void	draw_filled_circle(t_cubed *cubed, t_vector *center, int radius)
{
	int y = (int)center->y - radius;
	int x;
	int	delta_y;
	int	delta_x;
	int drawn = 0;

	while (y <= (int)center->y + radius)
	{
		x = (int)center->x - radius;
		delta_y= y - (int)center->y;
		while (x < (int)center->x + radius)
		{
			delta_x = x - (int)center->x;
			if (delta_x * delta_x + delta_y * delta_y <= radius * radius)
			{
				drawn = 1;
				ft_pixel_put(((t_cubed_bonus *)cubed)->minimap_img, x, y, center->color);
			}
			else if (drawn == 1)
				break ;
			x++;
		}
		drawn = 0;
		y++;
	}
}

void	test_circle(t_cubed *cubed)
{
	float		radius;
	t_vector	center;

	radius = 106;
	center.x = 300;//set to correct location on image for center
	center.y = 300;//
	center.color = RED;
	// while (radius > 0)
	// {
	// 	ft_bresenham_circle(cubed, &center, radius);
	// 	radius -= 0.07;
	// }
	draw_filled_circle(cubed, &center, radius);
}

t_vector	get_player_cell(t_player *player)
{
	t_vector	grid;

	grid.x = (int)player->location.x / CELL_SIZE;
	grid.y = (int)player->location.y / CELL_SIZE;
	return (grid);
}

unsigned int	get_color(t_map *map, int grid_x, int grid_y)
{
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0 || grid_y >= map->height)
		return (BLACK);//black
	else
	{
		if (map->grid[grid_y][grid_x] == '1')
			return (NAVY_BLUE); //navy blue
		else
			return (PINK); //pink
	}
}

void	draw_minimap(t_cubed *cubed, t_scene *scene)
{
	scene = NULL;//
	test_circle(cubed);
	// t_vector	player_loc;
	// t_vector	start;
	// int			grid_x;
	// int			grid_y;

	// player_loc = get_player_cell(&cubed->scene->player);
	// start.x = 0;
	// grid_x = player_loc.x - 3;
	// while (grid_x < (int)player_loc.x + 3)
	// {
	// 	start.y = 0;
	// 	grid_y = player_loc.y - 3;
	// 	while (grid_y < (int)player_loc.y + 3)
	// 	{
	// 		start.color = get_color(&cubed->scene->map, grid_x, grid_y);
	// 		my_put_square(((t_cubed_bonus *)cubed)->minimap_img, start, MINI_MAP_CELL);
	// 		start.y += MINI_MAP_CELL;
	// 		grid_y++;
	// 	}
	// 	start.x += MINI_MAP_CELL;
	// 	grid_x++;
	// }
}

//TODO move to bonus entire file
// void	draw_minimap(t_cubed *cubed, t_scene *scene)
// {
// 	int			i;
// 	int			j;
// 	t_vector	start;

// 	i = 0;
// 	start.x = 0;
// 	start.y = 0;
// 	while (i < scene->map.height)
// 	{
// 		j = 0;
// 		while (j < scene->map.width)
// 		{
// 			if (scene->map.grid[i][j] == '1')
// 				start.color = RED;
// 			else
// 				start.color = YELLOW;
// 			my_put_square(((t_cubed_bonus *)cubed)->minimap_img, start, CELL_SIZE);
// 			j++;
// 			start.x += CELL_SIZE;
// 		}
// 		start.x = 0;
// 		start.y += CELL_SIZE;
// 		i++;
// 	}
// 	printf("MAP DRAWN\n");
// 	start.x = 0;
// 	start.y = 0;
// 	start.color = 0x00FF00;
// 	my_put_grid(((t_cubed_bonus *)cubed)->minimap_img, &start, scene->map.width, \
// 	scene->map.height);
// }

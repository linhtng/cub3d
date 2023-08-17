/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 16:07:30 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

//TODO move to bonus entire file
// t_vector	get_player_cell(t_player *player)
// {
// 	t_vector	grid;

// 	grid.x = (int)player->location.x / CELL_SIZE;
// 	grid.y = (int)player->location.y / CELL_SIZE;
// 	return (grid);
// }

// unsigned int	get_color(t_map *map, int grid_x, int grid_y)
// {
// 	if (grid_x < 0 || grid_x >= map->width || grid_y < 0 || grid_y >= map->height)
// 		return (BLACK);//black
// 	else
// 	{
// 		if (map->grid[grid_y][grid_x] == '1')
// 			return (NAVY_BLUE); //navy blue
// 		else
// 			return (PINK); //pink
// 	}
// }

// void	draw_minimap(t_cubed *cubed, t_scene *scene)
// {
// 	scene = NULL;//
// 	t_vector	player_loc;
// 	t_vector	start;
// 	int			grid_x;
// 	int			grid_y;

// 	player_loc = get_player_cell(&cubed->scene->player);
// 	start.x = 0;
// 	grid_x = player_loc.x - 3;
// 	while (grid_x < (int)player_loc.x + 3)
// 	{
// 		start.y = 0;
// 		grid_y = player_loc.y - 3;
// 		while (grid_y < (int)player_loc.y + 3)
// 		{
// 			start.color = get_color(&cubed->scene->map, grid_x, grid_y);
// 			my_put_square(((t_cubed_bonus *)cubed)->minimap_img, start, MINI_MAP_CELL);
// 			start.y += MINI_MAP_CELL;
// 			grid_y++;
// 		}
// 		start.x += MINI_MAP_CELL;
// 		grid_x++;
// 	}
// }

//TODO move to bonus entire file
void	draw_minimap(t_cubed *cubed, t_scene *scene)
{
	int			i;
	int			j;
	t_vector	start;

	i = 0;
	start.x = 0;
	start.y = 0;
	while (i < scene->map.height)
	{
		j = 0;
		while (j < scene->map.width)
		{
			if (scene->map.grid[i][j] == '1')
				start.color = 0xFF0000;//red
			else
				start.color = 0x666666;
			my_put_square(((t_cubed_bonus *)cubed)->minimap_img, start, CELL_SIZE);
			j++;
			start.x += CELL_SIZE;
		}
		start.x = 0;
		start.y += CELL_SIZE;
		i++;
	}
	printf("MAP DRAWN\n");
	start.x = 0;
	start.y = 0;
	start.color = 0x00FF00;
	my_put_grid(((t_cubed_bonus *)cubed)->minimap_img, &start, scene->map.width, \
	scene->map.height);
}

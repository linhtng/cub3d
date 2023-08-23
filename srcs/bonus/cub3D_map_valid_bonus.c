/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_valid_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:07 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/23 19:07:12 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	get_flood_start_point(t_scene *scene, t_vector *start)
{
	int	row;
	int	col;

	row = 0;
	while (row < scene->map.height)
	{
		col = 0;
		while (col < scene->map.width)
		{
			if (scene->map.flood[row][col] == '1')
			{
				start->y = row;
				start->x = col;
				return ;
			}
			col++;
		}
		row++;
	}
}

int	check_island(t_scene *scene, char **grid)
{
	int			unfilled;
	int			line;
	t_vector	flood_start;

	line = 0;
	unfilled = 0;
	if (!(big_frame_map(grid, scene) == 1
			&& empty_map(scene) == 1))
		return (ERROR);
	get_flood_start_point(scene, &flood_start);
	scene->map.flood_old = '1';
	scene->map.flood_new = FLOODED_WALL;
	ft_flood(flood_start.y, flood_start.x, scene, SPACE);
	while (line < scene->map.height + 2)
	{
		unfilled += count_occurences(scene->map.flood[line], \
		scene->map.flood_old);
		if (unfilled)
			return (err_msg("Map has isolated island. ", "Invalid."));
		line++;
	}
	return (1);
}

void	ft_flood(int y, int x, t_scene *scene, char block)
{
	if (y < 0 || x < 0 || y >= (scene->map.height + 2)
		|| x >= (int)ft_strlen(scene->map.flood[y])
		|| scene->map.flood[y][x] == block
		|| scene->map.visited[y][x] == VISITED)
		return ;
	scene->map.visited[y][x] = VISITED;
	if (scene->map.flood[y][x] == scene->map.flood_old)
		scene->map.flood[y][x] = scene->map.flood_new;
	if (scene->map.flood_new == EXPOSED
		&& ft_strchr(MAP_CONTENT, scene->map.flood[y][x]))
		scene->map.flood[y][x] = scene->map.flood_new;
	ft_flood(y + 1, x, scene, block);
	ft_flood(y - 1, x, scene, block);
	ft_flood(y, x + 1, scene, block);
	ft_flood(y, x - 1, scene, block);
}

int	big_frame_map(char **map, t_scene *scene)
{
	char	**dup;
	int		i;

	dup = (char **) ft_calloc(scene->map.height + 3, sizeof(char *));
	if (!dup)
		return (err_msg("Malloc err when getting the map content.", NULL));
	scene->map.flood = dup;
	i = 0;
	while (i < scene->map.height + 2)
	{
		dup[i] = (char *) calloc(scene->map.width + 3, sizeof(char));
		if (!dup[i])
			return (err_msg("Malloc err when getting the map content.", NULL));
		ft_memset(dup[i], SPACE, scene->map.width + 2);
		if (i && i < (scene->map.height + 1))
			ft_memmove(&(dup[i][1]), map[i - 1], ft_strlen(map[i - 1]));
		i++;
	}
	return (1);
}

int	empty_map(t_scene *scene)
{
	char	**empty;
	int		i;

	empty = (char **) ft_calloc(scene->map.height + 3, sizeof(char *));
	if (!empty)
		return (err_msg("Malloc err when getting the map content.", NULL));
	scene->map.visited = empty;
	i = 0;
	while (i < scene->map.height + 2)
	{
		empty[i] = (char *) calloc(scene->map.width + 3, sizeof(char));
		if (!empty[i])
			return (err_msg("Malloc err when getting the map content.", NULL));
		ft_memset(empty[i], '0', scene->map.width + 2);
		i++;
	}
	return (1);
}

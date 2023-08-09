/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:28:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/09 18:40:56 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	player_pos_valid(char **map, t_player player, char block)
{
	if (map[(int)player.location.y][(int)player.location.x + 1] == block
		&& map[(int)player.location.y + 1][(int)player.location.x] == block
		&& map[(int)player.location.y][(int)player.location.x - 1] == block
		&& map[(int)player.location.y - 1][(int)player.location.x] == block)
		return (err_msg(1, "Invalid postion. Player can't moved from here."));
	return (1);
}

static int	create_map(t_scene *scene, char **scene_arr)
{
	char	**map;
	int		line;
	int		line_len;

	map = (char **) ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!map)
		return (err_msg(1, "Malloc err when getting the map content."));
	scene->map.array = map;
	line = 0;
	while (line < scene->map.height)
	{
		map[line] = (char *) ft_calloc(scene->map.width + 1, sizeof(char));
		if (!map[line])
			return (err_msg(1, "Malloc err when getting the map content."));
		line_len = ft_strlen(scene_arr[line]);
		ft_memset(map[line], SPACE, scene->map.width);
		ft_memmove(map[line], scene_arr[line], line_len);
		while (line_len-- > 0)
		{
			if (map[line][line_len] == ' ')
				map[line][line_len] = SPACE;
		}
		line++;
	}
	return (1);
}

int	map_valid_characters(t_scene *scene, char *line, int y)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (!ft_strchr("01NSEW ", line[index]))
			return (err_msg(2, "Map has invalid character in line:", line));
		if (ft_strchr("NSEW", line[index]))
		{
			if (!scene->player.spawn)
			{
				scene->player.spawn = (char) line[index];
				scene->player.location.x = index;
				scene->player.location.y = y;
			}
			else
				return (err_msg(1, "Map must have only 1 player."));
		}
		index++;
	}
	return (1);
}

int	check_island(t_scene *scene, char **map)
{
	int	island;
	int	line;

	line = 0;
	island = 0;
	if (!(ft_arrdup(map, scene) == 1
			&& empty_map(scene) == 1))
		return (ERROR);
	//print_arr(scene->map.flood);
	//printf("map height: %d\n", scene->map.height);
	/* printf("map flood before flood start:\n");
	print_arr(scene->map.flood); */
	/* printf("map visited before flood start:\n");
	print_arr(scene->map.visited); */
	ft_flood(scene->player.location.y, scene->player.location.x, scene);
	/* printf("map flooded:\n");
	print_arr(scene->map.flood); */
	while (line < scene->map.height)
	{
		island += count_occurences(scene->map.flood[line], '1');
		if (island)
			return (err_msg(1, "Map has isolated island. Invalid."));
		line++;
	}
	return (1);
}

int	get_map_content(char **scene_arr, t_scene *scene, int i)
{
	int	w;
	int	empty_space;

	i = 0;
	empty_space = 0;
	while (scene_arr[i])
	{
		if (map_valid_characters(scene, scene_arr[i], i) == ERROR)
			return (ERROR);
		w = ft_strlen(scene_arr[i]);
		if (w > scene->map.width)
			scene->map.width = w;
		empty_space += count_occurences(scene_arr[i], '0');
		i++;
	}
	if (!empty_space || !scene->player.spawn)
		return (err_msg(1, "Map missing empty space and/or player."));
	if (create_map(scene, scene_arr) == ERROR)
		return (ERROR);
	if (valid_walls(scene, scene->map.array) == ERROR
		|| player_pos_valid(scene->map.array, scene->player, '1') == ERROR
		|| player_pos_valid(scene->map.array, scene->player, SPACE) == ERROR)
		return (ERROR);
	return (check_island(scene, scene->map.array));
}

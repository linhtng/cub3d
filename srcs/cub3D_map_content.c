/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:28:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/27 21:34:04 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	lay_space_holder(char *map_line)
{
	int		i;
	int		len;
	char	*endl;

	endl = ft_strrchr(map_line, '1');
	if (!endl)
		return (err_msg(1, "Encounter map content line without wall."));
	len = (int)(endl - map_line);
	i = 0;
	while (ft_isspace(map_line[i]))
		i++;
	while (i < len)
	{
		if (map_line[i] == ' ')
			map_line[i] = '_';
		i++;
	}
	return (1);
}

static int	player_pos_valid(char **map, t_player player)
{
	if (map[player.pos_y][player.pos_x + 1] == '1'
		&& map[player.pos_y + 1][player.pos_x] == '1'
		&& map[player.pos_y][player.pos_x - 1] == '1'
		&& map[player.pos_y - 1][player.pos_x] == '1')
		return (err_msg(1, "Player is surround by walls and can't moved."));
	return (1);
}

static int	create_map(t_scene *scene, char **scene_arr)
{
	char	**map;
	int		line;

	map = (char **) ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!map)
		return (err_msg(1, "Malloc err when getting the map content."));
	scene->map.array = map;
	line = 0;
	while (line < scene->map.height)
	{
		map[line] = ft_strdup(scene_arr[line]);
		if (!map[line])
			return (err_msg(1, "Malloc err when getting the map content."));
		if (lay_space_holder(map[line]) == ERROR)
			return (ERROR);
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
		if (!ft_strchr("01NSEW\n ", line[index]))
			return (err_msg(2, "Map has invalid character in line:", line));
		if (ft_strchr("NSEW", line[index]))
		{
			if (!scene->player.spawn)
			{
				scene->player.spawn = (char) line[index];
				scene->player.pos_x = index;
				scene->player.pos_y = y;
			}
			else
				return (err_msg(1, "Map must have only 1 player."));
		}
		index++;
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
	if (valid_walls(scene, scene->map.array) == ERROR)
		return (ERROR);
	return (player_pos_valid(scene->map.array, scene->player));
}

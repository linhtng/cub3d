/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:28:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/09/02 16:08:21 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* 
 * player_pos_valid() checks if the player is stucked surrounded by walls 
*/
static int	player_pos_valid(char **map, t_player player, char block)
{
	if (map[(int)player.location.y][(int)player.location.x + 1] == block
		&& map[(int)player.location.y + 1][(int)player.location.x] == block
		&& map[(int)player.location.y][(int)player.location.x - 1] == block
		&& map[(int)player.location.y - 1][(int)player.location.x] == block)
		return (err_msg("Invalid postion. ", "Player can't moved from here."));
	return (1);
}

/* 
 * create_map() creates a 2D array of the map, copy the corresponding line
 * from the scene array to the map array.The area outside the map is filled 
 * with spaces. The spaces inside the map are filled with '_'.
*/
static int	create_map(t_scene *scene, char **scene_arr)
{
	char	**map;
	int		line;
	int		line_len;

	map = (char **) ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!map)
		return (err_msg("Malloc err when getting the map content.", NULL));
	scene->map.grid = map;
	line = 0;
	while (line < scene->map.height)
	{
		map[line] = (char *) ft_calloc(scene->map.width + 1, sizeof(char));
		if (!map[line])
			return (err_msg("Malloc err when getting the map content.", NULL));
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

/* 
 * map_valid_characters() checks if the map contains only valid characters,
 * and if there is only one player. 
 * It also saves the player's spawn location. 
*/
int	map_valid_characters(t_scene *scene, char *line, int y)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (!ft_strchr(VALID_CHARS, line[index]))
			return (err_msg("Map has invalid character in line: ", line));
		if (ft_strchr("NSEW", line[index]))
		{
			if (!scene->player.spawn)
			{
				scene->player.spawn = (char) line[index];
				scene->player.location.x = index;
				scene->player.location.y = y;
			}
			else
				return (err_msg("Map must have only 1 player.", NULL));
		}
		index++;
	}
	return (1);
}

/*
 * check_island() checks if the map is entirely surrounded by walls. 
 * If there is any map content that get exposed instead of 
 * surrounded by walls, flood fill algorithm will fill it with 'I'.
 * Any detected 'I' means the map is not entirely surrounded by walls.
*/
int	map_is_exposed(t_scene *scene)
{
	int			unfilled;
	int			line;

	line = 0;
	unfilled = 0;
	while (line < scene->map.height + 2)
	{
		ft_memset(scene->map.visited[line], '0', scene->map.width + 2);
		line++;
	}
	scene->map.flood_old = '0';
	scene->map.flood_new = EXPOSED;
	ft_flood(0, 0, scene, FLOODED_WALL);
	line = 0;
	while (line < scene->map.height + 2)
	{
		unfilled += count_occurences(scene->map.flood[line], EXPOSED);
		if (unfilled)
		{
			return (err_msg("Map is not entirely closed by walls. ", 
					"Invalid."));
		}
		line++;
	}
	return (1);
}

/*
 * get_map_content() gets the map content from the scene array.
 * It checks if any misconfiguration of any kind is encountered 
 * in the file, including invalid characters, missing map components,
 * invalid player position, isolated island, and exposed map content
 * instead of surrounded by walls.
*/
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
		return (err_msg("Map missing empty space and/or player.", NULL));
	if (create_map(scene, scene_arr) == ERROR)
		return (ERROR);
	if (player_pos_valid(scene->map.grid, scene->player, '1') == ERROR
		|| check_island(scene, scene->map.grid) == ERROR
		|| map_is_exposed(scene) == ERROR)
		return (ERROR);
	return (1);
}

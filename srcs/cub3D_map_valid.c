/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:07 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/05 21:07:33 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_only(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != SPACE)
		{
			printf("map line not closed by wall: %s", str);
			return (0);
		}
		i++;
	}
	return (1);
}

/* valid_walled:
*	Example:
*	A-------B
*	|		|
*	|		|
*	D-------C
*/

int	valid_walls(t_scene *scene, char **map)
{
	int	i;
	int	j;
	int	len;

	if (!wall_only(map[0]) || !wall_only(map[scene->map.height - 1]))
		return (err_msg(1, "The map must be closed/surrounded by walls."));
	i = 1;
	while (i < scene->map.height)
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (ft_isspace(map[i][len - 1]))
			len--;
		while (ft_isspace(map[i][j]))
			j++;
		if (map[i][j] != '1' || map[i][len - 1] != '1')
		{
			printf("map line not closed by wall: %s\n", map[i]); //debug, dell later
			return (err_msg(1, "The map must be closed/surrounded by walls."));
		}
		i++;
	}
	return (1);
}

int	cell_inbound(int i, int j, t_scene *scene)
{
	return (i >= 0 && i < scene->map.height && j >= 0 && j < scene->map.width);
}

void	ft_flood(int x, int y, t_scene *scene)
{
	//printf("map height: %d\n", scene->map.height);
	if (y < 0 || x < 0 || y >= scene->map.height || x >= (int)ft_strlen(scene->map.flood[y])
		|| (scene->map.flood[y][x] != '0' && scene->map.flood[y][x] != '1' 
		&& !ft_strchr("NSEW", scene->map.flood[y][x])))
	{
		printf("y: %d x: %d\n", y, x);
		return ;
	}
	//printf("map flood current line: %s\n", scene->map.flood[y]);
	if ((scene->map.flood[y][x] == '0' || scene->map.flood[y][x] == '1'))
		scene->map.flood[y][x] = '2';
	//printf("flood start:\n");
	printf("map flood current line: %s\n", scene->map.flood[y]);
	//map[y][x] += 2;
	//print_arr(map);
	ft_flood(y + 1, x, scene);
	ft_flood(y - 1, x, scene);
	ft_flood(y, x + 1, scene);
	ft_flood(y, x - 1, scene);
}

int	ft_arrdup(char **map, t_scene *scene)
{
	char	**dup;
	int		i;

	dup = (char **) ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!dup)
		return (err_msg(1, "Malloc err when getting the map content."));
	scene->map.flood = dup;
	i = 0;
	while (i < scene->map.height)
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
			return (err_msg(1, "Malloc err when getting the map content."));
		i++;
	}
	return (1);
}

int	empty_map(t_scene *scene)
{
	char	**empty;
	int		i;

	empty = (char **) ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!empty)
		return (err_msg(1, "Malloc err when getting the map content."));
	scene->map.visited = empty;
	i = 0;
	while (i < scene->map.height)
	{
		empty[i] = (char *) malloc(sizeof(char) * (scene->map.width + 1));
		if (!empty[i])
			return (err_msg(1, "Malloc err when getting the map content."));
		ft_memset(empty[i], '0', scene->map.width);
		empty[i][scene->map.width] = '\0';
		i++;
	}
	return (1);
}

int	check_island(t_scene *scene, char **map)
{
	if (!(ft_arrdup(map, scene) == 1
		&& empty_map(scene) == 1))
		return (ERROR);
	//print_arr(scene->map.flood);
	ft_flood(scene->player.pos_x, scene->player.pos_y, scene);
	printf("map flooded:\n");
	print_arr(scene->map.flood);
	printf("end\n");
	//print_arr(map);
	return (1);
}


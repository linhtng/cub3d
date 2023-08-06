/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:07 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/06 21:07:44 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] == SPACE)
		i++;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != SPACE)
			return (0);
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
		while (map[i][len - 1] == SPACE)
			len--;
		while (map[i][j] == SPACE)
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

void	ft_flood(int y, int x, t_scene *scene)
{
	if (y < 0 || x < 0 || y >= scene->map.height
		|| x >= (int)ft_strlen(scene->map.flood[y])
		|| scene->map.flood[y][x] == SPACE
		|| scene->map.visited[y][x] == VISITED)
	{
		//printf("y: %d x: %d\n", y, x);
		return ;
	}
	//printf("map flood current line: %s\n", scene->map.flood[y]);
	scene->map.visited[y][x] = VISITED;
	if ((scene->map.flood[y][x] == '0' || scene->map.flood[y][x] == '1'))
		scene->map.flood[y][x] = '2';
	//printf("flood start:\n");
	//printf("map flood current line: %s\n", scene->map.flood[y]);
	//map[y][x] += 2;
	//print_arr(map);
	ft_flood(y + 1, x, scene);
	ft_flood(y - 1, x, scene);
	ft_flood(y, x + 1, scene);
	ft_flood(y, x - 1, scene);
	ft_flood(y + 1, x + 1, scene);
	ft_flood(y + 1, x - 1, scene);
	ft_flood(y - 1, x + 1, scene);
	ft_flood(y - 1, x - 1, scene);
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
	printf("map height: %d\n", scene->map.height);
	printf("map flood before flood start:\n");
	print_arr(scene->map.flood);
	/* int	i = 0;
	while (i < scene->map.height)
		printf("len of each line in flood: %d\n", (int)ft_strlen(scene->map.flood[i++])); */
	printf("map visited before flood start:\n");
	print_arr(scene->map.visited);
	printf("player pos y: %d, pos x: %d\n", scene->player.pos_y, scene->player.pos_x);
	ft_flood(scene->player.pos_y, scene->player.pos_x, scene);
	printf("map flooded:\n");
	print_arr(scene->map.flood);
	printf("map visited after:\n");
	print_arr(scene->map.visited);
	printf("end\n");
	//print_arr(map);
	return (1);
}

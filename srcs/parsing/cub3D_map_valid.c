/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:07 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/08 21:59:47 by thuynguy         ###   ########.fr       */
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
		while (len && (map[i][len - 1] == SPACE))
			len--;
		if (!len)
			return (err_msg(1, "Empty line detected in map content."));
		while (map[i][j] && (map[i][j] == SPACE))
			j++;
		if (map[i][j] != '1' || map[i][len - 1] != '1')
			return (err_msg(1, "The map must be closed/surrounded by walls."));
		i++;
	}
	return (1);
}

void	ft_flood(int y, int x, t_scene *scene)
{
	if (y < 0 || x < 0 || y >= scene->map.height
		|| x >= (int)ft_strlen(scene->map.flood[y])
		|| scene->map.flood[y][x] == SPACE
		|| scene->map.visited[y][x] == VISITED)
		return ;
	scene->map.visited[y][x] = VISITED;
	if ((scene->map.flood[y][x] == '0' || scene->map.flood[y][x] == '1'))
		scene->map.flood[y][x] = '2';
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

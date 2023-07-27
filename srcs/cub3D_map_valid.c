/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:07 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/27 21:39:24 by thuynguy         ###   ########.fr       */
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
		if (str[i] != '1' && str[i] != '_')
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

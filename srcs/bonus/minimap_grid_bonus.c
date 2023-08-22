/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:03:50 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/21 17:15:06 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	get_bonus_grid(t_scene *scene)
{
	int	line;

	line = 0;
	while (line < scene->map.height + 2)
	{
		ft_memset(scene->map.visited[line], '0', scene->map.width + 2);
		line++;
	}
	scene->map.flood_old = SPACE;
	scene->map.flood_new = BONUS_CHAR;
	ft_flood(0, 0, scene, FLOODED_WALL);
}

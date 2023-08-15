/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/15 19:49:54 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast_bonus.h"
#include "libft.h"
#include "cub3D_bonus.h"


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
			my_put_square(cubed->minimap_img, start, CELL_SIZE);
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
	my_put_grid(cubed->minimap_img, &start, scene->map.width, \
	scene->map.height);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 12:46:01 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

void	draw_minimap(t_cubed *cubed, t_scene *scene)
{
	int i;
	int j;
	t_vector start;

	i = 0;
	start.x = 0;
	start.y = 0;
	while (i < scene->lines)
	{
		j = 0;
		while (j < scene->columns)
		{
			if (scene->map[i][j] == '1')
				start.color = 0xFF0000;//red
			else if (scene->map[i][j] == '0')
				start.color = 0x666666;
			else
			{
				start.color = 0x666666;//gray
				printf("PLAYER DRAWN\n");
				setup_player(cubed, i, j, scene->map[i][j]);//
			}
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
	my_put_grid(cubed->minimap_img, &start, scene->columns, scene->lines);
}

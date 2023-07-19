/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/19 18:31:35 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
// // [4][5]
// char **MAP_1 = {
// 	"11111",
// 	"10001",
// 	"1N001",
// 	"11111"
// };
// // [7][10]
// char **MAP_2 = {
// 	"1111111111",
// 	"1000000001",
// 	"1N00000001",
// 	"1000111111",
// 	"1000000001",
// 	"1000000001",
// 	"1111111111"
// };

void	draw_minimap(t_cubed *cubed)
{
// [4][5]
	char *MAP_1[4] = {
		"11111",
		"10001",
		"1N001",
		"11111"
	};

	t_img_data img;
	int i;
	int j;
	t_vector start;

	img.img = mlx_new_image(cubed->mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &(img.bits_per_pixel), &(img.line_length),  &(img.endian));
	cubed->img = &img;
	i = 0;
	start.x = 0;
	start.y = 0;
	// start.color = 0xFFFF00;//
	// my_put_square(&img, &start, 32);
	while (i < 4)//for hardcoded example
	{
		j = 0;
		while (j < 5)
		{
			if (MAP_1[i][j] == '1')
				start.color = 0xFF0000;//red
			else if (MAP_1[i][j] == '0')
				start.color = 0x666666;
			else
			{
				start.color = 0x666666;//yellow
				cubed->player.y = i * 32;
				cubed->player.x = j * 32;
				cubed->player.color = 0xFFFF00;
			}
			my_put_square(&img, start, 32);
			j++;
			start.x += 32;
		}
		start.x = 0;
		start.y += 32;
		i++;
	}
	start.x = 0;
	start.y = 0;
	start.color = 0x00FF00;
	my_put_grid(&img, &start, 32, 5, 4);
	my_put_square(&img, cubed->player, 10);
	
	mlx_put_image_to_window(cubed->mlx, cubed->window, img.img, 0, 0);
}

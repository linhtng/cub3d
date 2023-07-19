/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/19 17:03:54 by jebouche         ###   ########.fr       */
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


void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	my_put_line_h(t_img_data *data, t_vector *start, int len)
{
	int		i;
	int		x;

	i = 0;
	x = start->x;
	while (i < len)
	{
		my_mlx_pixel_put(data, start->x, start->y, start->color);
		start->x++;
		i++;
	}
	start->x = x;
}

void	my_put_line_v(t_img_data *data, t_vector *start, int len)
{
	int		i;
	int		y;

	i = 0;
	y = start->y;
	while (i < len)
	{
		my_mlx_pixel_put(data, start->x, start->y, start->color);
		start->y++;
		i++;
	}
	start->y = y;
}

void	my_put_grid(t_img_data *data, t_vector *start, int	sq_size, int len, int height)
{
	int	i;
	t_vector	line_loc;

	i = 0;
	line_loc.x = start->x;
	line_loc.y = start->y;
	line_loc.color = 0x00FF0F;
	my_put_line_h(data, start, len * sq_size);
	my_put_line_v(data, start, height * sq_size);
	while (i < height)
	{
		line_loc.y += sq_size;
		my_put_line_h(data, &line_loc, len * sq_size);
		i++;
	}
	i = 0;
	line_loc.x = start->x;
	line_loc.y = start->y;
	while ( i < len)
	{
		line_loc.x += sq_size;
		my_put_line_v(data, &line_loc, height * sq_size);
		i++;
	}
}
//change to be solid square
//start already at upper left hand corner
void	my_put_square(t_img_data *data, t_vector start, int len)
{
	int	i;

	i = 0;

	while (i < len)
	{
		my_put_line_v(data, &start, len);
		start.x++;
		i++;
	}
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/26 18:24:38 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

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

void	draw_player(t_cubed *cubed, t_scene *scene)
{
	t_vector	player_loc;
	char		direction;

	// cubed->player_img->img = mlx_new_image(cubed->mlx, WIN_WIDTH, WIN_HEIGHT);//
	// cubed->player_img->addr = mlx_get_data_addr(cubed->player_img->img, &(cubed->player_img->bits_per_pixel), &(cubed->player_img->line_length),  &(cubed->player_img->endian));
	ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//creates transparent
	player_loc = cubed->player.location;
	direction = scene->map[(int) cubed->player.location.y / CELL_SIZE][(int) cubed->player.location.x / CELL_SIZE];
	printf("PLAYER CHARACTER IS: %c\n", direction);
	if (direction == 'N')
	{
		player_loc.y -= 10;
		cubed->player.angle = 90.0f;
		my_put_line_v(cubed->player_img, &player_loc, 10);
	}
	if (direction == 'S')
	{
		player_loc.y += 10;
		cubed->player.angle = 270.0f;
		my_put_line_v(cubed->player_img, &player_loc, 10);
	}
	if (direction == 'E')
	{
		player_loc.x += 10;
		cubed->player.angle = 0.0f;
		my_put_line_h(cubed->player_img, &player_loc, 10);
	}
	if (direction == 'W')
	{
		player_loc.x -= 10;
		cubed->player.angle = 180.0f;
		my_put_line_h(cubed->player_img, &player_loc, 10);
	}
	my_put_square(cubed->player_img, cubed->player.location, 10);
}

void	setup_player(t_cubed *cubed, int i, int j, char dir)
{
	t_vector temp;

	cubed->player.location.y = i * CELL_SIZE + CELL_SIZE / 2;
	cubed->player.location.x = j * CELL_SIZE + CELL_SIZE / 2;
	cubed->player.location.color = 0xFFFF00;//yellow
	if (dir == 'N')
		cubed->player.angle = 90.0f;
	if (dir == 'S')
		cubed->player.angle = 270.0f;
	if (dir == 'E')
		cubed->player.angle = 0.0f;
	if (dir == 'W')
		cubed->player.angle = 180.0f;
	cubed->player.d.x = cos(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.d.y = sin(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.distance_to_pane = 0;//TODO setup use for distance to pane
	cubed->player.height = 0;//TODO setup use for player height
	//draw inital dir and loc
	ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);
	my_put_square(cubed->player_img, cubed->player.location, 10);
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
}

void	draw_minimap(t_cubed *cubed, t_scene *scene)
{
	int i;
	int j;
	t_vector start;

	// cubed->img->img = mlx_new_image(cubed->mlx, WIN_WIDTH, WIN_HEIGHT);//segfaults???
	// img.img = mlx_new_image(cubed->mlx, WIN_WIDTH, WIN_HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &(img.bits_per_pixel), &(img.line_length),  &(img.endian));
	// cubed->img = &img;
	i = 0;
	start.x = 0;
	start.y = 0;
	// start.color = 0xFFFF00;//
	// my_put_square(&img, &start, CELL_SIZE);
	while (i < scene->lines)//for hardcoded example
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
				// cubed->player.location.y = i * CELL_SIZE + CELL_SIZE / 2;
				// cubed->player.location.x = j * CELL_SIZE + CELL_SIZE / 2;
				// cubed->player.location.color = 0xFFFF00;//yellow
			}
			my_put_square(cubed->img, start, CELL_SIZE);
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
	my_put_grid(cubed->img, &start, scene->columns, scene->lines);

	//draw player
	// draw_player(cubed, scene);
	// shoot_one_ray_horizontal(cubed, scene, 60.0f);//
	// shoot_one_ray_vertical(cubed, scene, 60.0f);//
	// shoot_one_ray_horizontal(cubed, scene, 125.0f);//
	// shoot_one_ray_vertical(cubed, scene, 125.0f);//
	// shoot_one_ray_horizontal(cubed, scene, 196.0f);//
	// shoot_one_ray_vertical(cubed, scene, 196.0f);//
	// shoot_one_ray_horizontal(cubed, scene, 287.0f);//
	// shoot_one_ray_vertical(cubed, scene, 287.0f);//
	//render order?
	// mlx_put_image_to_window(cubed->mlx, cubed->window, img.img, 0, 0);
	// mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->player_img->img, 0, 0);
}

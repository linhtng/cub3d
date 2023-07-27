/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/27 11:28:10 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"

void	refresh_images(t_cubed *cubed)
{
	mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->img->img, 0, 0);
	mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->player_img->img, 0, 0);
}

void	turn_player(t_cubed *cubed, int key_code)
{
	t_vector temp;
	printf("player should look some direction...\n");
	
	if (key_code == TURN_LEFT)
	{
		cubed->player.angle = correct_degrees(cubed->player.angle + 1);//turn 5 deg at a time
	}
	else
	{
		cubed->player.angle = correct_degrees(cubed->player.angle - 1);//turn 5 deg at a time	
	}
	cubed->player.d.x = cos(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.d.y = sin(deg_to_rad(cubed->player.angle)) * 5;
	//redraw
	ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
	my_put_square(cubed->player_img, cubed->player.location, 10);
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
	printf("PLAYER ANGLE: %f\n", cubed->player.angle);//
	cast_rays(cubed);
	refresh_images(cubed);
}

int	handle_press(int key_code, t_cubed *cubed)
{
	t_vector temp;

	printf("KEY PRESSED: %i\n", key_code);
	if (key_code == ESC)
		mlx_close(cubed, 0, "Normal exit");
	if (key_code == TURN_LEFT || key_code == TURN_RIGHT)
		turn_player(cubed, key_code);
	if (key_code == FORWARD)
	{
		printf("player whould go forward\n");
		cubed->player.location.y -= 5;
		ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
		my_put_square(cubed->player_img, cubed->player.location, 10);
		temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
		temp.y = cubed->player.location.y + cubed->player.d.y * 5;
		ft_bresenham(cubed->player.location, temp, cubed->player_img);
		cast_rays(cubed);
		refresh_images(cubed);
	}
	if (key_code == LEFT)
	{
		printf("player whould go left\n");
		cubed->player.location.x -= 5;
		ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
		my_put_square(cubed->player_img, cubed->player.location, 10);
		temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
		temp.y = cubed->player.location.y + cubed->player.d.y * 5;
		ft_bresenham(cubed->player.location, temp, cubed->player_img);
		cast_rays(cubed);
		refresh_images(cubed);

	}
	if (key_code == BACK)
	{
		printf("player whould go backward\n");
		cubed->player.location.y += 5;
		ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
		my_put_square(cubed->player_img, cubed->player.location, 10);
		temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
		temp.y = cubed->player.location.y + cubed->player.d.y * 5;
		ft_bresenham(cubed->player.location, temp, cubed->player_img);
		cast_rays(cubed);
		refresh_images(cubed);

	}
	if (key_code == RIGHT)
	{
		printf("player whould go right\n");
		cubed->player.location.x += 5;
		ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
		my_put_square(cubed->player_img, cubed->player.location, 10);
		temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
		temp.y = cubed->player.location.y + cubed->player.d.y * 5;
		ft_bresenham(cubed->player.location, temp, cubed->player_img);
		cast_rays(cubed);
		refresh_images(cubed);
	}
	
	return (0);
}
/* ATTEMPTS to move player */
		// // mlx_destroy_image(cubed->mlx, cubed->player_img->img);
		// cubed->player.y -= 1;
		// ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
		// my_put_square(cubed->player_img, cubed->player, 10);
		// // mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->img->img, 0, 0);
		// mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->player_img->img, 0, 0);
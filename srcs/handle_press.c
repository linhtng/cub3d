/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/20 10:06:36 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"

int	handle_press(int key_code, t_cubed *cubed)
{
	printf("KEY PRESSED: %i\n", key_code);
	if (key_code == ESC)
		mlx_close(cubed, 0, "Normal exit");
	if (key_code == TURN_LEFT || key_code == TURN_RIGHT)
		printf("player should look some direction...\n");
	if (key_code == FORWARD)
	{
		printf("player whould go forward\n");
	}
	if (key_code == LEFT)
		printf("player whould go left\n");
	if (key_code == BACK)
		printf("player whould go backward\n");
	if (key_code == RIGHT)
		printf("player whould go right\n");
	return (0);
}
/* ATTEMPTS to move player */
		// // mlx_destroy_image(cubed->mlx, cubed->player_img->img);
		// cubed->player.y -= 1;
		// ft_memset(cubed->player_img->addr, 0x00FFFFFF, WIN_WIDTH * WIN_HEIGHT);//createes transparent
		// my_put_square(cubed->player_img, cubed->player, 10);
		// // mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->img->img, 0, 0);
		// mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->player_img->img, 0, 0);
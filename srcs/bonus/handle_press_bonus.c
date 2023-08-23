/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/23 19:32:24 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_cubed *cubed)
{
	mlx_close(cubed, 0, "normal exit");
	return (0);
}

/* int	handle_press(int key_code, t_cubed *cubed)
{
	if (key_code == ESC)
		mlx_close(cubed, 0, "Normal exit");
	if (key_code == TURN_LEFT || key_code == TURN_RIGHT)
		turn_player(cubed, key_code);
	if (key_code == FORWARD || key_code == BACK)
	{
		move_forward_backward(cubed, key_code);
	}
	if (key_code == LEFT || key_code == RIGHT)
	{
		move_right_left(cubed, key_code);
	}
	if (cubed->dirty_images)
		refresh_images(cubed);
	return (0);
} */

int	handle_press(int key_code, t_cubed *cubed)
{
	int i = 0;

	while (i < 8)
	{
		printf("[handle press] key num %d, value %d\n", i, cubed->keys[i]);
		i++;
	}
	if (cubed->keys[ESC_PRESSED])
		mlx_close(cubed, 0, "Normal exit");
	if (cubed->keys[LEFT_PRESSED] || cubed->keys[RIGHT_PRESSED])
		turn_player(cubed, key_code);
	if (cubed->keys[W_PRESSED] || cubed->keys[S_PRESSED])
	{
		move_forward_backward(cubed, key_code);
	}
	if (cubed->keys[A_PRESSED] || cubed->keys[D_PRESSED])
	{
		move_right_left(cubed, key_code);
	}
	if (cubed->dirty_images)
		refresh_images(cubed);
	return (0);
}
int	key_press(int key_code, t_cubed_bonus *cubed)
{
	// if (key_code == ESC)
	// 	cubed->key[ESC_PRESSED] = 1;
	// if (key_code == TURN_LEFT)
	// 	cubed->key[LEFT_PRESSED] = 1;
	// if (key_code == TURN_RIGHT)
	// 	cubed->key[RIGHT_PRESSED] = 1;
	// if (key_code == FORWARD)
	// 	cubed->key[W_PRESSED] = 1;
	// if (key_code == BACK)
	// 	cubed->key[S_PRESSED] = 1;
	// if (key_code == LEFT)
	// 	cubed->key[A_PRESSED] = 1;
	// if (key_code == RIGHT)
	// 	cubed->key[D_PRESSED] = 1;
	// if (key_code == OPEN_DOOR)
	// 	cubed->key[SPACE_BAR] = 1;
	cubed->key_pressed = key_code;
	return (0);
}
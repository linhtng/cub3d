/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/23 19:39:04 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

// int	handle_press(int key_code, t_cubed *cubed)
// {
// 	int i = 0;

// 	while (i < 8)
// 	{
// 		printf("[handle press] key num %d, value %d\n", i, cubed->keys[i]);
// 		i++;
// 	}
// 	if (cubed->keys[ESC_PRESSED])
// 		mlx_close(cubed, 0, "Normal exit");
// 	if (cubed->keys[LEFT_PRESSED] || cubed->keys[RIGHT_PRESSED])
// 		turn_player(cubed, key_code);
// 	if (cubed->keys[W_PRESSED] || cubed->keys[S_PRESSED])
// 	{
// 		move_forward_backward(cubed, key_code);
// 	}
// 	if (cubed->keys[A_PRESSED] || cubed->keys[D_PRESSED])
// 	{
// 		move_right_left(cubed, key_code);
// 	}
int	handle_press(int key_code, t_cubed *cubed)
{
	if (key_code == ESC)
		mlx_close(cubed, 0, "Normal exit");
	else if (key_code == TURN_LEFT || key_code == TURN_RIGHT)
		turn_player(cubed, key_code);
	else if (key_code == FORWARD || key_code == BACK)
		move_forward_backward(cubed, key_code);
	else if (key_code == LEFT || key_code == RIGHT)
		move_right_left(cubed, key_code);
	else if (key_code == INTERACT)
		check_interaction((t_cubed_bonus *)cubed);
	if (cubed->dirty_images)
		refresh_images(cubed);
	return (0);
}

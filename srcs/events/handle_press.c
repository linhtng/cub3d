/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 19:28:15 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_cubed *cubed)
{
	mlx_close(cubed, 0, "normal exit");
	return (0);
}

int	handle_press(int key_code, t_cubed *cubed)
{
	if (key_code == ESC)
		mlx_close(cubed, 0, "Normal exit");
	if (key_code == TURN_LEFT || key_code == TURN_RIGHT)
		turn_player(cubed, key_code);
	if (key_code == FORWARD || key_code == BACK)
		move_forward_backward(cubed, key_code);
	if (key_code == LEFT || key_code == RIGHT)
		move_right_left(cubed, key_code);
	if (cubed->dirty_images)
		refresh_images(cubed);
	return (0);
}

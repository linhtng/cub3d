/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/06 20:47:18 by jebouche         ###   ########.fr       */
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
		turn_player(cubed, key_code);
	if (key_code == FORWARD)
	{
		move_forward(cubed);
	}
	if (key_code == LEFT)
	{
		move_left(cubed);
	}
	if (key_code == BACK)
	{
		move_backward(cubed);
	}
	if (key_code == RIGHT)
	{
		move_right(cubed);
	}
	//put check for 'dirty images' and refresh of images here
	return (0);
}

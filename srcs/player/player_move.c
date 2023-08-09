/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:43:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 11:37:09 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

void	turn_player(t_cubed *cubed, int key_code)
{
	if (key_code == TURN_LEFT)
		cubed->player.angle = correct_degrees(cubed->player.angle + 5);
	else
		cubed->player.angle = correct_degrees(cubed->player.angle - 5);
	cubed->player.d.x = cos(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.d.y = -sin(deg_to_rad(cubed->player.angle)) * 5;
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

void	move_forward_backward(t_cubed *cubed, int key_code)
{
	if (key_code == FORWARD)
	{
		cubed->player.location.x += cubed->player.d.x;
		cubed->player.location.y += cubed->player.d.y;
	}
	else
	{
		cubed->player.location.x -= cubed->player.d.x;
		cubed->player.location.y -= cubed->player.d.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}
void	move_right_left(t_cubed *cubed, int	key_code)
{
	float		move_angle;
	
	if (key_code == RIGHT)
		move_angle = correct_degrees(cubed->player.angle - 90.0f);
	else
		move_angle = correct_degrees(cubed->player.angle + 90.0f);
	cubed->player.location.x += cos(deg_to_rad(move_angle)) * 5;
	cubed->player.location.y += -sin(deg_to_rad(move_angle)) * 5;
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

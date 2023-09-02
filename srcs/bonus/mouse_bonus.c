/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:01 by thuynguy          #+#    #+#             */
/*   Updated: 2023/09/02 16:39:15 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * mouse_move() checks if the mouse is moved within the projection pane bounds
 * and updates the player angle and direction accordingly.
*/
int	mouse_move(int x, int y, void *param)
{
	t_cubed_bonus	*cubed;

	cubed = (t_cubed_bonus *)param;
	if (y >= 0 && y < PROJECTION_HEIGHT && x >= 0 && x < PROJECTION_WIDTH)
	{
		cubed->scene->player.angle = correct_degrees(cubed->scene->player.angle 
				- (x - cubed->mouse_x) / 3);
		cubed->scene->player.d.x = 
			cos(deg_to_rad(cubed->scene->player.angle)) * PLAYER_SPEED;
		cubed->scene->player.d.y = 
			-sin(deg_to_rad(cubed->scene->player.angle)) * PLAYER_SPEED;
	}
	cubed->mouse_x = x;
	return (0);
}

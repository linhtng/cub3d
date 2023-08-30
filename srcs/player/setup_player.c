/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:12:52 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 16:03:43 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * setup_player() sets the player's location, color, angle and direction based
 * on the parsed map values.
*/
void	setup_player(t_cubed *cubed)
{
	cubed->scene->player.location.y = cubed->scene->player.location.y * \
	CELL_SIZE + CELL_SIZE / 2;
	cubed->scene->player.location.x = cubed->scene->player.location.x * \
	CELL_SIZE + CELL_SIZE / 2;
	cubed->scene->player.location.color = RED;
	if (cubed->scene->player.spawn == 'N')
		cubed->scene->player.angle = 90.0f;
	if (cubed->scene->player.spawn == 'S')
		cubed->scene->player.angle = 270.0f;
	if (cubed->scene->player.spawn == 'E')
		cubed->scene->player.angle = 0.0f;
	if (cubed->scene->player.spawn == 'W')
		cubed->scene->player.angle = 180.0f;
	cubed->scene->player.d.x = \
	cos(deg_to_rad(cubed->scene->player.angle)) * PLAYER_SPEED;
	cubed->scene->player.d.y = \
	-sin(deg_to_rad(cubed->scene->player.angle)) * PLAYER_SPEED;
}

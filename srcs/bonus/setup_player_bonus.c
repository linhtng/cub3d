/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:12:52 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 14:37:20 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_raycast_bonus.h"
// #include "cub3D_bonus.h"

#include "cub3D.h"

//TODO add bonus condition for draw mini player
void	setup_player(t_cubed *cubed)
{
	t_vector	start;

	start.x = 0;
	start.y = 0;
	start.color = 0x00;
	cubed->scene->player.location.y = cubed->scene->player.location.y * \
	CELL_SIZE + CELL_SIZE / 2;
	cubed->scene->player.location.x = cubed->scene->player.location.x * \
	CELL_SIZE + CELL_SIZE / 2;
	cubed->scene->player.location.color = 0xFFFF00;//yellow
	if (cubed->scene->player.spawn == 'N')
		cubed->scene->player.angle = 90.0f;
	if (cubed->scene->player.spawn == 'S')
		cubed->scene->player.angle = 270.0f;
	if (cubed->scene->player.spawn == 'E')
		cubed->scene->player.angle = 0.0f;
	if (cubed->scene->player.spawn == 'W')
		cubed->scene->player.angle = 180.0f;
	cubed->scene->player.d.x = cos(deg_to_rad(cubed->scene->player.angle)) * 5;
	cubed->scene->player.d.y = -sin(deg_to_rad(cubed->scene->player.angle)) * 5;
	draw_mini_player(cubed);//maybe take out????
}

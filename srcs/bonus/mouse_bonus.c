/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:01 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/29 16:41:47 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	mouse_move(int x, int y, void *param)
{
	t_cubed_bonus	*cubed;

	cubed = (t_cubed_bonus *)param;
	if (y >= 0 && y < PROJECTION_HEIGHT && x >= 0 && x < PROJECTION_WIDTH)
	{
		cubed->scene->player.angle = correct_degrees(cubed->scene->player.angle \
		- (x - cubed->mouse_x) / 3);
		cubed->scene->player.d.x = \
		cos(deg_to_rad(cubed->scene->player.angle)) * 5;
		cubed->scene->player.d.y = \
		-sin(deg_to_rad(cubed->scene->player.angle)) * 5;
	}
	cubed->mouse_x = x;
	return (0);
}

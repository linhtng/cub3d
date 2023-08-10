/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:43:43 by jebouche          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/10 10:31:13 by jebouche         ###   ########.fr       */
=======
/*   Updated: 2023/08/09 21:27:10 by thuynguy         ###   ########.fr       */
>>>>>>> b00d8ad679687d3b0f40eabf5ae0d0c6e2cfd2c9
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

//return true / false? setup buffer to + or - based on direction?  010
//currently allows movement through small gaps, eg. from 0 to 0 -> 101 
int	can_move(t_cubed *cubed, t_vector *next)
{
	t_vector	grid;

	grid.x = ((int)next->x) / CELL_SIZE;
	grid.y = ((int)next->y) / CELL_SIZE;
	// printf("[CAN MOVE NEXT] y %f, x %f", next->y, next->x);
	// printf("[CAN MOVE MAP CONTENT] y cell = %i x cell = %i char = %c\n", (int) grid.y, (int) grid.x, cubed->scene->map[(int) grid.y][(int) grid.x]);
	if (cubed->scene->map.grid[(int)grid.y][(int)grid.x] && cubed->scene->map.grid[(int) grid.y][(int) grid.x] == '1')
		return (0);
	return (1);
}

void	turn_player(t_cubed *cubed, int key_code)
{	
	if (key_code == TURN_LEFT)
		cubed->scene->player.angle = \
		correct_degrees(cubed->scene->player.angle + 5);
	else
		cubed->scene->player.angle = \
		correct_degrees(cubed->scene->player.angle - 5);
	cubed->scene->player.d.x = cos(deg_to_rad(cubed->scene->player.angle)) * 5;
	cubed->scene->player.d.y = -sin(deg_to_rad(cubed->scene->player.angle)) * 5;
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

void	move_forward_backward(t_cubed *cubed, int key_code)
{
	t_vector	next_loc;

	if (key_code == FORWARD)
	{
		next_loc.x = cubed->scene->player.location.x + cubed->scene->player.d.x;
		next_loc.y = cubed->scene->player.location.y + cubed->scene->player.d.y;
	}
	else
	{
		next_loc.x = cubed->scene->player.location.x - cubed->scene->player.d.x;
		next_loc.y = cubed->scene->player.location.y - cubed->scene->player.d.y;
	}
	if (can_move(cubed, &next_loc))
	{
		cubed->scene->player.location.x = next_loc.x;
		cubed->scene->player.location.y = next_loc.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

void	move_right_left(t_cubed *cubed, int key_code)
{
	t_vector	next_loc;
	float		move_angle;

	if (key_code == RIGHT)
		move_angle = correct_degrees(cubed->scene->player.angle - 90.0f);
	else
		move_angle = correct_degrees(cubed->scene->player.angle + 90.0f);
	next_loc.x = cubed->scene->player.location.x + \
	cos(deg_to_rad(move_angle)) * 5;
	next_loc.y = cubed->scene->player.location.y + \
	-sin(deg_to_rad(move_angle)) * 5;
	if (can_move(cubed, &next_loc))
	{
		cubed->scene->player.location.x = next_loc.x;
		cubed->scene->player.location.y = next_loc.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

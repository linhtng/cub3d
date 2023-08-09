/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:43:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 14:23:28 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

//return true / false? setup buffer to + or - based on direction?
int	can_move(t_cubed *cubed, t_vector *next)
{
	t_vector grid;
	
	grid.x = ((int)next->x) / CELL_SIZE;
	grid.y = ((int)next->y) / CELL_SIZE;
	// printf("[CAN MOVE NEXT] y %f, x %f", next->y, next->x);
	// printf("[CAN MOVE MAP CONTENT] y cell = %i x cell = %i char = %c\n", (int) grid.y, (int) grid.x, cubed->scene->map[(int) grid.y][(int) grid.x]);
	if (cubed->scene->map[(int)grid.y][(int)grid.x] && cubed->scene->map[(int) grid.y][(int) grid.x] == '1')
		return (0);
	return (1);
}

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
	t_vector 	next_loc;

	if (key_code == FORWARD)
	{
		next_loc.x = cubed->player.location.x + cubed->player.d.x;
		next_loc.y = cubed->player.location.y + cubed->player.d.y;
	}
	else
	{
		next_loc.x = cubed->player.location.x - cubed->player.d.x;
		next_loc.y = cubed->player.location.y - cubed->player.d.y;
	}
	if (can_move(cubed, &next_loc))
	{
		cubed->player.location.x = next_loc.x;
		cubed->player.location.y = next_loc.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}
void	move_right_left(t_cubed *cubed, int	key_code)
{
	t_vector 	next_loc;
	float		move_angle;
	
	if (key_code == RIGHT)
		move_angle = correct_degrees(cubed->player.angle - 90.0f);
	else
		move_angle = correct_degrees(cubed->player.angle + 90.0f);
	next_loc.x = cubed->player.location.x + cos(deg_to_rad(move_angle)) * 5;
	next_loc.y = cubed->player.location.y + -sin(deg_to_rad(move_angle)) * 5;
	if (can_move(cubed, &next_loc))
	{
		cubed->player.location.x = next_loc.x;
		cubed->player.location.y = next_loc.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

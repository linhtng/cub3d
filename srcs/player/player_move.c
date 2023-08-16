/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:03:20 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 21:54:37 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	collision_dist(int axis, int key_code, t_vector *next)
{
	int	backward;

	if (key_code == FORWARD || key_code == RIGHT)
		backward = 1;
	else
		backward = -1;
	if (axis == pane_y)
	{
		if (next->y > 0)
			return (COLLISION_DISTANCE * backward);
		else
			return (-COLLISION_DISTANCE * backward);
	}
	else
	{
		if (next->x > 0)
			return (COLLISION_DISTANCE * backward);
		else
			return (-COLLISION_DISTANCE * backward);
	}
}

//return true / false? setup buffer to + or - based on direction?  010
//currently allows movement through small gaps, eg. from 0 to 0 -> 101 
//TODO decide if for bonus only or not
int	can_move(t_cubed *cubed, t_vector *next, int key_code)
{
	t_vector	grid;
	t_vector	collision_check;

	grid.x = ((int)next->x) / CELL_SIZE;
	grid.y = ((int)next->y) / CELL_SIZE;
	collision_check.x = collision_dist(0, key_code, next);
	collision_check.y = collision_dist(1, key_code, next);
	printf("[CAN MOVE NEXT] y %f, x %f", next->y, next->x);
	printf("[CAN MOVE MAP CONTENT] y cell = %i x cell = %i char = %c\n", (int) grid.y, (int) grid.x, cubed->scene->map.grid[(int) grid.y][(int) grid.x]);
	if (cubed->scene->map.grid[(int)grid.y][(int)grid.x] && cubed->scene->map.grid[(int) grid.y][(int) grid.x] == '1')
		return 0;
	printf("[collision_dist] y cell = %i x cell = %i \n", (int)(grid.y + collision_check.y), (int) grid.x);
	printf("[Map content at collision_dist check point 1] y %c\n", cubed->scene->map.grid[(int)(grid.y + collision_check.y)][(int)grid.x]);
	printf("[collision_dist] y cell = %i x cell = %i \n", (int)(grid.y), (int)(grid.x + collision_check.x));
	printf("[Map content at collision_dist check point 2] y %c\n", cubed->scene->map.grid[(int)(grid.y)][(int)(grid.x + collision_check.x)]);
	if (cubed->scene->map.grid[(int)(grid.y + collision_check.y)][(int)grid.x] == '1'
		& cubed->scene->map.grid[(int)(grid.y)][(int)(grid.x + collision_check.x)] == '1')
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
	if (can_move(cubed, &next_loc, key_code))
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
	if (can_move(cubed, &next_loc, key_code))
	{
		cubed->scene->player.location.x = next_loc.x;
		cubed->scene->player.location.y = next_loc.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

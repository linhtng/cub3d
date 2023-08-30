/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:03:20 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 19:57:12 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * collision_detect() checks if the player is going to move though a gap
 * between two walls. It does this by checking if the two corners of the
 * player's target cell are empty. If they are, the player can move through 
 * the gap. It finds the location of the two corner the same way we find the 
 * coordinates of the two vertices 3 and 4 of a square given the 1 and 2
 * vertices. Example:
 * 1-------3
 * |	   |
 * |	   |
 * 4-------2
*/
int	collision_detect(char **grid, t_vector center, t_vector half_diagon)
{
	t_vector	third_corner;
	t_vector	fourth_corner;

	third_corner.y = center.y - half_diagon.x;
	third_corner.x = center.x + half_diagon.y;
	fourth_corner.y = center.y + half_diagon.x;
	fourth_corner.x = center.x - half_diagon.y;
	if ((grid[(int)third_corner.y][(int)third_corner.x]
		&& grid[(int)third_corner.y][(int)third_corner.x] == '1')
		&& (grid[(int)fourth_corner.y][(int)fourth_corner.x]
		&& grid[(int)fourth_corner.y][(int)fourth_corner.x] == '1'))
		return (0);
	return (1);
}

/*
 * can_move() checks if the player can move to the next location. It checks 
 * if the next location is the same as the current cell, if not it will check
 * surrounding cells for walls and return 0 if there is a wall. 
*/
int	can_move(t_cubed *cubed, t_vector *next)
{
	t_vector	grid;
	t_vector	player_cell;
	t_vector	center;
	t_vector	half_diagon;

	grid.x = ((int)next->x) / CELL_SIZE;
	grid.y = ((int)next->y) / CELL_SIZE;
	player_cell.x = ((int)cubed->scene->player.location.x) / CELL_SIZE;
	player_cell.y = ((int)cubed->scene->player.location.y) / CELL_SIZE;
	if (cubed->scene->map.grid[(int)grid.y][(int)grid.x]
		&& cubed->scene->map.grid[(int) grid.y][(int) grid.x] == '1')
		return (0);
	if ((int)grid.y == (int)player_cell.y || (int)grid.x == (int)player_cell.x)
		return (1);
	else
	{
		center.y = ((int)grid.y + (int)player_cell.y) / 2.0f;
		center.x = ((int)grid.x + (int)player_cell.x) / 2.0f;
		half_diagon.y = ((int)grid.y - (int)player_cell.y) / 2.0f;
		half_diagon.x = ((int)grid.x - (int)player_cell.x) / 2.0f;
		return (collision_detect(cubed->scene->map.grid, center, half_diagon));
	}
}

/*
 * turn_player() turns the player left or right by 5 degrees. It then updates
 * the player's direction vector and calls redraw() to redraw the scene.
*/
void	turn_player(t_cubed *cubed, int key_code)
{
	if (key_code == TURN_LEFT)
		cubed->scene->player.angle = \
		correct_degrees(cubed->scene->player.angle + 5);
	else
		cubed->scene->player.angle = \
		correct_degrees(cubed->scene->player.angle - 5);
	cubed->scene->player.d.x = \
	cos(deg_to_rad(cubed->scene->player.angle)) * PLAYER_SPEED;
	cubed->scene->player.d.y = \
	-sin(deg_to_rad(cubed->scene->player.angle)) * PLAYER_SPEED;
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

/*
 * move_forward_backward() moves the player forward or backward by PLAYER_SPEED
 * by referencing the player directions. It then calls redraw() to redraw 
 * the scene.
*/
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

/*
 * move_right_left() moves the player right or left by PLAYER_SPEED by 
 * calclating the perpendicular angle to the player's direction, 
 * either +/- 90 degrees. It then calls redraw() to redraw the scene.
*/
void	move_right_left(t_cubed *cubed, int key_code)
{
	t_vector	next_loc;
	float		move_angle;

	if (key_code == RIGHT)
		move_angle = correct_degrees(cubed->scene->player.angle - 90.0f);
	else
		move_angle = correct_degrees(cubed->scene->player.angle + 90.0f);
	next_loc.x = cubed->scene->player.location.x + \
	cos(deg_to_rad(move_angle)) * PLAYER_SPEED;
	next_loc.y = cubed->scene->player.location.y + \
	-sin(deg_to_rad(move_angle)) * PLAYER_SPEED;
	if (can_move(cubed, &next_loc))
	{
		cubed->scene->player.location.x = next_loc.x;
		cubed->scene->player.location.y = next_loc.y;
	}
	redraw(cubed);
	cubed->dirty_images = TRUE;
}

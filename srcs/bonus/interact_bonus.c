/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:44:41 by jebouche          #+#    #+#             */
/*   Updated: 2023/09/02 16:38:11 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * get_player_cell_content() returns the content of the cell the player is
 * standing on.
*/
static char	get_player_cell_content(t_cubed_bonus *cubed)
{
	int	x;
	int	y;

	x = (int)cubed->scene->player.location.x / CELL_SIZE;
	y = (int)cubed->scene->player.location.y / CELL_SIZE;
	return (cubed->scene->map.grid[y][x]);
}

/*
 * get_in_range_content() returns the content of the cell in range of the
 * player. The range is defined by the INTERACTION_DISTANCE macro.
*/
static char	get_in_range_content(t_cubed_bonus *cubed)
{
	int	x;
	int	y;

	x = (int)(cubed->scene->player.location.x + 
			(cubed->scene->player.d.x / 3.0f) * 
			(double)INTERACTION_DISTANCE) / CELL_SIZE;
	y = (int)(cubed->scene->player.location.y + 
			(cubed->scene->player.d.y / 3.0f) * 
			(double)INTERACTION_DISTANCE) / CELL_SIZE;
	return (cubed->scene->map.grid[y][x]);
}

/*
 * get_new_grid_value() returns the new value of the grid based on the found
 * character. By default if the interactable is not a door the value is set to
 * OPEN_SPACE.
*/
static char	get_new_grid_value(char found)
{
	if (found == DOOR_CLOSED)
		return (DOOR_OPEN);
	else if (found == DOOR_OPEN)
		return (DOOR_CLOSED);
	else
		return (OPEN_SPACE);
}

/*
 * change_grid_value() changes the value of the grid based on the found
 * character.
*/
static void	change_grid_value(t_cubed_bonus *cubed, 
char found, int player_or_range)
{
	char	new_value;
	int		row;
	int		col;

	new_value = get_new_grid_value(found);
	if (player_or_range == 0)
	{
		row = (int)cubed->scene->player.location.x / CELL_SIZE;
		col = (int)cubed->scene->player.location.y / CELL_SIZE;
	}
	else
	{
		row = (int)(cubed->scene->player.location.x + 
				(cubed->scene->player.d.x / 3.0f) * 
				(double)INTERACTION_DISTANCE) / CELL_SIZE;
		col = (int)(cubed->scene->player.location.y + 
				(cubed->scene->player.d.y / 3.0f) * 
				(double)INTERACTION_DISTANCE) / CELL_SIZE;
	}
	cubed->scene->map.grid[col][row] = new_value;
}

/*
 * check_interaction() checks if the player is in range of an interactable
 * object. If the player is in range of an interactable object, the object is
 * changed to the next state. If the player is standing on an interactable
 * object, the object is changed to the next state.
*/
void	check_interaction(t_cubed_bonus *cubed)
{
	char	player_cell;
	char	in_range;

	cubed->keys[SPACE_BAR] = 0;
	player_cell = get_player_cell_content(cubed);
	in_range = get_in_range_content(cubed);
	if (ft_strchr(INTERACTABLE_HERE, player_cell))
		change_grid_value(cubed, player_cell, 0);
	else if (ft_strchr(INTERACTABLE_NEARBY, in_range))
		change_grid_value(cubed, in_range, 1);
	else
		return ;
	redraw((t_cubed *)cubed);
	cubed->dirty_images = TRUE;
}

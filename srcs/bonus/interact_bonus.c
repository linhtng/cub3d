/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:44:41 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 14:23:44 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static char	get_player_cell_content(t_cubed_bonus *cubed)
{
	int	x;
	int	y;

	x = (int)cubed->scene->player.location.x / CELL_SIZE;
	y = (int)cubed->scene->player.location.y / CELL_SIZE;
	return (cubed->scene->map.grid[y][x]);
}

static char	get_in_range_content(t_cubed_bonus *cubed)
{
	int	x;
	int	y;

	x = (int)(cubed->scene->player.location.x + \
	(cubed->scene->player.d.x / 3.0f) * \
	(float)INTERACTION_DISTANCE) / CELL_SIZE;
	y = (int)(cubed->scene->player.location.y + \
	(cubed->scene->player.d.y / 3.0f) * \
	(float)INTERACTION_DISTANCE) / CELL_SIZE;
	return (cubed->scene->map.grid[y][x]);
}

//default to remove interactable character
static char	get_new_grid_value(char found)
{
	if (found == DOOR_CLOSED)
		return (DOOR_OPEN);
	else if (found == DOOR_OPEN)
		return (DOOR_CLOSED);
	else
		return (OPEN_SPACE);
}

static void	change_grid_value(t_cubed_bonus *cubed, \
char found, int player_or_range)
{
	char	new_value;

	new_value = get_new_grid_value(found);
	if (player_or_range == 0)
	{
		cubed->scene->map.grid \
		[(int)cubed->scene->player.location.y / CELL_SIZE] \
		[(int)cubed->scene->player.location.x / CELL_SIZE] = new_value;
	}
	else
	{
		cubed->scene->map.grid \
		[(int)(cubed->scene->player.location.y + \
		(cubed->scene->player.d.y / 3.0f) * \
		(float)INTERACTION_DISTANCE) / CELL_SIZE][(int) \
		(cubed->scene->player.location.x + (cubed->scene->player.d.x / 3.0f) * \
		(float)INTERACTION_DISTANCE) / CELL_SIZE] = new_value;
	}
}

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

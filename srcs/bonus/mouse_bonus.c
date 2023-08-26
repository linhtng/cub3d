/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:01 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/26 20:51:26 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int mouse_move(int x, int y, void *param)
{
    t_cubed_bonus	*cubed;

    cubed = (t_cubed_bonus *)param;
    //printf("[mouse move] map dimension y: %d, x: %d\n", cubed->scene->map.height, cubed->scene->map.width);
    printf("[mouse move] mouse pose y: %d, x: %d\n", y / CELL_SIZE, x / CELL_SIZE);
    if (y >= 0 && (y / CELL_SIZE) < cubed->scene->map.height
        && x >= 0 && (x / CELL_SIZE) < cubed->scene->map.width)
        cubed->scene->player.angle -= (x - cubed->mouse_x) / 3;
    cubed->mouse_x = x;
    return (0);
}
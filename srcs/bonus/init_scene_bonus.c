/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:18:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 16:07:25 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(&scene->elems, 0, sizeof(t_elem));
	ft_memset(&scene->map, 0, sizeof(t_map));
	ft_memset(&scene->player, 0, sizeof(t_player));
	ft_memset(&scene->map.start, 0, sizeof(t_vector));
	scene->elems.north = NULL;
	scene->elems.south = NULL;
	scene->elems.east = NULL;
	scene->elems.west = NULL;
	scene->array = NULL;
	scene->map.grid = NULL;
	scene->map.flood = NULL;
	scene->map.visited = NULL;
	ft_memset(((t_scene_bonus *)scene)->bonus_elems.ceiling, '\0', \
	sizeof(((t_scene_bonus *)scene)->bonus_elems.ceiling));
	((t_scene_bonus *)scene)->bonus_elems.floor = NULL;
	((t_scene_bonus *)scene)->bonus_elems.door = NULL;
}

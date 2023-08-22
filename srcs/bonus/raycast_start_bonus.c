/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/21 17:12:08 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	raycast_start(t_scene *scene)
{
	t_cubed_bonus	cubed_bonus;
	t_cubed			*cubed;
	t_raycast		raycast_info;

	cubed = (t_cubed *) &cubed_bonus;
	setup_cubed(cubed);
	get_bonus_grid(scene);
	cubed->scene = scene;
	setup_raycast(cubed, &raycast_info);
	setup_player(cubed);
	load_texture(scene, cubed);
	redraw(cubed);
	draw_background(cubed);
	refresh_images(cubed);
	mlx_hook(cubed->window, 17, 0, close_window, cubed);
	mlx_hook(cubed->window, 2, 1L << 0, handle_press, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/15 21:18:32 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

int	raycast_start(t_scene *scene)
{
	t_cubed		cubed;
	t_raycast	raycast_info;

	setup_cubed(&cubed);
	cubed.scene = scene;
	setup_raycast(&cubed, &raycast_info);
	setup_player(&cubed);
	load_texture(scene, &cubed);
	//DRAW STUFF initial render
	draw_minimap(&cubed, scene); //draws base, not called again
	cubed.scene->player.location.color = 0x000FFF;//
	redraw(&cubed);//draws the first time
	draw_background(&cubed);//called once to setup the background
	refresh_images(&cubed);//images to windows
	mlx_hook(cubed.window, 17, 0, &mlx_close, &cubed);
	mlx_hook(cubed.window, 2, 1L << 0, handle_press, &cubed);
	mlx_loop(cubed.mlx);
	return (0);
}

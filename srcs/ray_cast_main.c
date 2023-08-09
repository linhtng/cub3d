/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 19:13:29 by thuynguy         ###   ########.fr       */
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
	print_scene(cubed.scene);
	setup_raycast(&cubed, &raycast_info);
	setup_player(&cubed);
	/* hardcoded map, colors */
	/* scene.map = MAP_2;
	int color1 = 0X91a3db;
	int color2 = 0X91a358;
	scene.ceiling_color = &color1;
	scene.floor_color = &color2; */
	/* end hardcoded map, colors */

	//DRAW STUFF
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
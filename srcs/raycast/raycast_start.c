/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/09/02 16:03:27 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * raycast_start() is the main function for the raycasting. It sets up the 
 * cubed struct and the raycast_info struct. It sets up the player struct, 
 * loads the textures, draws the bacground and renders the intial view. It then
 * sets up the mlx hooks and starts the mlx loop. 
*/
int	raycast_start(t_scene *scene)
{
	t_cubed		cubed;
	t_raycast	raycast_info;

	setup_cubed(&cubed);
	cubed.scene = scene;
	setup_raycast(&cubed, &raycast_info);
	setup_player(&cubed);
	load_texture(scene, &cubed);
	draw_background(&cubed);
	redraw(&cubed);
	refresh_images(&cubed);
	mlx_hook(cubed.window, 17, 0, close_window, &cubed);
	mlx_hook(cubed.window, 2, 1L << 0, handle_press, &cubed);
	mlx_loop(cubed.mlx);
	return (0);
}

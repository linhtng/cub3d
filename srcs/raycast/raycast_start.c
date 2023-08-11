/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/11 11:11:58 by jebouche         ###   ########.fr       */
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

	//DRAW STUFF initial render
	draw_minimap(&cubed, scene); //draws base, not called again
	cubed.scene->player.location.color = 0x000FFF;//
	redraw(&cubed);//draws the first time
	// /* XPM TESTS */
	// t_img_data xpm_test;
	// xpm_test.img = mlx_xpm_file_to_image(cubed.mlx, "textures/test.xpm", &xpm_test.width, &xpm_test.height);
	// xpm_test.addr = mlx_get_data_addr(xpm_test.img, &xpm_test.bits_per_pixel, &xpm_test.line_length, &xpm_test.endian);
	// /* XPM TEST END */
	draw_background(&cubed);//called once to setup the background
	refresh_images(&cubed);//images to windows
	// mlx_put_image_to_window(cubed.mlx, cubed.window, xpm_test.img, 100, 500);

	mlx_hook(cubed.window, 17, 0, &mlx_close, &cubed);
	mlx_hook(cubed.window, 2, 1L << 0, handle_press, &cubed);
	mlx_loop(cubed.mlx);
	return (0);
}

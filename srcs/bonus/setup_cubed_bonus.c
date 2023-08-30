/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cubed_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:34:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 15:41:33 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	zero_cubed(t_cubed_bonus *cubed)
{
	cubed->mlx = NULL;
	cubed->window = NULL;
	cubed->dirty_images = 0;
	cubed->raycast_info = NULL;
	cubed->scene = NULL;
	cubed->frame_img = NULL;
	cubed->mini_player_img = NULL;
	cubed->minimap_img = NULL;
	ft_memset(cubed->keys, 0, sizeof(cubed->keys));
	cubed->key_pressed = -1;
	cubed->animated_frame = 0;
	cubed->mouse_x = 0;
}

static void	setup_cubed_images(t_cubed *cubed)
{
	((t_cubed_bonus *)cubed)->minimap_img = \
	get_new_image(cubed, MINI_MAP_DIAMETER, MINI_MAP_DIAMETER);
	((t_cubed_bonus *)cubed)->mini_player_img = \
	get_new_image(cubed, MINI_MAP_DIAMETER, MINI_MAP_DIAMETER);
	((t_cubed_bonus *)cubed)->frame_img = \
	get_new_xpm_image(cubed, "texture_src/cubed_frame.xpm");
}

void	setup_cubed(t_cubed *cubed)
{
	int	frame_fd;

	zero_cubed((t_cubed_bonus *) cubed);
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		mlx_close(cubed, 1, "intialization of mlx failed");
	cubed->window = mlx_new_window(cubed->mlx, WIN_WIDTH, WIN_HEIGHT, \
	"Cubikat");
	if (!cubed->window)
		mlx_close(cubed, 1, "intialization of mlx window failed");
	frame_fd = open("texture_src/cubed_frame.xpm", O_RDWR);
	if (frame_fd == ERROR)
	{
		close(frame_fd);
		mlx_close(cubed, 1, "Cub3d: Error: No frame texture detected");
	}
	close(frame_fd);
	setup_cubed_images(cubed);
	ft_memset(((t_cubed_bonus *)cubed)->minimap_img->addr, TRANSPARENT, \
	MINI_MAP_DIAMETER * MINI_MAP_DIAMETER * \
	(((t_cubed_bonus *)cubed)->mini_player_img->bits_per_pixel / 8));
}

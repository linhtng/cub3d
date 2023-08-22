/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cubed_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:34:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 20:00:34 by thuynguy         ###   ########.fr       */
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
	cubed->reward_img = NULL;
	cubed->reward.animated_frame = 0;
}
static void	setup_reward(t_cubed *cubed)
{
	int reward_fd;

	reward_fd = open("texture_src/reward.xpm", O_RDWR);
	if (reward_fd == ERROR)
	{
		close(reward_fd);
		mlx_close(cubed, 1, "Cub3d: Error: No reward texture detected");
	}
	close(reward_fd);
	((t_cubed_bonus *)cubed)->reward_img = \
	get_new_xpm_image(cubed, "texture_src/reward.xpm");
	((t_cubed_bonus *)cubed)->reward.pos.y = \
	(PROJECTION_HEIGHT - ((t_cubed_bonus *)cubed)->reward_img->height) / 2;
	((t_cubed_bonus *)cubed)->reward.pos.x = \
	(PROJECTION_WIDTH - ((t_cubed_bonus *)cubed)->reward_img->width) / 2;
}

void	setup_cubed(t_cubed *cubed)
{
	int frame_fd;
	
	zero_cubed((t_cubed_bonus *) cubed);
	cubed->mlx = mlx_init();
	cubed->window = mlx_new_window(cubed->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	((t_cubed_bonus *)cubed)->minimap_img = \
	get_new_image(cubed, MINI_MAP_DIAMETER, MINI_MAP_DIAMETER);
	((t_cubed_bonus *)cubed)->mini_player_img = \
	get_new_image(cubed, MINI_MAP_DIAMETER, MINI_MAP_DIAMETER);
	frame_fd = open("texture_src/cubed_frame.xpm", O_RDWR);
	if (frame_fd == ERROR)
	{
		close(frame_fd);
		mlx_close(cubed, 1, "Cub3d: Error: No frame texture detected");
	}
	close(frame_fd);
	((t_cubed_bonus *)cubed)->frame_img = \
	get_new_xpm_image(cubed, "texture_src/cubed_frame.xpm");
	ft_memset(((t_cubed_bonus *)cubed)->minimap_img->addr, TRANSPARENT, \
	MINI_MAP_DIAMETER * MINI_MAP_DIAMETER * \
	(((t_cubed_bonus *)cubed)->mini_player_img->bits_per_pixel / 8));
	setup_reward(cubed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 20:01:28 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	animate_reward(void *param)
{
	t_cubed_bonus	*cubed;

	cubed = (t_cubed_bonus *)param;
	cubed->reward.animated_frame++;
	if (cubed->reward.animated_frame == ANIMATION_FRAME)
		cubed->reward.pos.y += 10;
	else if (cubed->reward.animated_frame == ANIMATION_FRAME * 2)
	{
		cubed->reward.pos.y -= 10;
		cubed->reward.animated_frame = 0;
	}
	refresh_images(param);
	return (0);
}

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
	mlx_loop_hook(cubed->mlx, animate_reward, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}

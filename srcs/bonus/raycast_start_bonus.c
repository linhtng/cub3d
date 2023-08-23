/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/23 19:23:40 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

// int	animate_reward(void *param)
// {
// 	t_cubed_bonus	*cubed;
// 	//static int		frame;

// 	cubed = (t_cubed_bonus *)param;
// 	cubed->reward.animated_frame++;
// 	if (cubed->reward.animated_frame == ANIMATION_FRAME)
// 		cubed->reward.pos.y += 10;
// 	else if (cubed->reward.animated_frame == ANIMATION_FRAME * 2)
// 	{
// 		cubed->reward.pos.y -= 10;
// 		cubed->reward.animated_frame = 0;
// 	}
// 	//printf("[animate reward] pos y: %f, pos x: %f\n", cubed->reward_pos.y, cubed->reward_pos.x);
// 	// mlx_put_image_to_window(cubed->mlx, cubed->window, \
// 	// cubed->reward_img->img, cubed->reward.pos.y, cubed->reward.pos.x);
// 	refresh_images(((t_cubed *)cubed));
// 	//cubed->dirty_images = TRUE;
// 	return (0);
// }

int	key_press(int key_code, t_cubed_bonus *cubed)
{
	if (key_code == ESC)
		cubed->keys[ESC_PRESSED] = 1;
	if (key_code == TURN_LEFT)
		cubed->keys[LEFT_PRESSED] = 1;
	if (key_code == TURN_RIGHT)
		cubed->keys[RIGHT_PRESSED] = 1;
	if (key_code == FORWARD)
		cubed->keys[W_PRESSED] = 1;
	if (key_code == BACK)
		cubed->keys[S_PRESSED] = 1;
	if (key_code == LEFT)
		cubed->keys[A_PRESSED] = 1;
	if (key_code == RIGHT)
		cubed->keys[D_PRESSED] = 1;
	if (key_code == OPEN_DOOR)
		cubed->keys[SPACE_BAR] = 1;
	cubed->key_pressed = key_code;
	return (0);
}

int	key_release(int key_code, t_cubed_bonus *cubed)
{
	if (key_code == ESC)
		cubed->keys[ESC_PRESSED] = 0;
	if (key_code == TURN_LEFT)
		cubed->keys[LEFT_PRESSED] = 0;
	if (key_code == TURN_RIGHT)
		cubed->keys[RIGHT_PRESSED] = 0;
	if (key_code == FORWARD)
		cubed->keys[W_PRESSED] = 0;
	if (key_code == BACK)
		cubed->keys[S_PRESSED] = 0;
	if (key_code == LEFT)
		cubed->keys[A_PRESSED] = 0;
	if (key_code == RIGHT)
		cubed->keys[D_PRESSED] = 0;
	if (key_code == OPEN_DOOR)
		cubed->keys[SPACE_BAR] = 0;
	return (0);
}

int	game_update(void *param)
{
	t_cubed_bonus	*cubed;

	cubed = (t_cubed_bonus *)param;
	handle_press(cubed->key_pressed, param);
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
	mlx_hook(cubed->window, 2, 1L << 0, key_press, cubed);
	mlx_hook(cubed->window, 3, 1L << 1, key_release, cubed);
	mlx_loop_hook(cubed->mlx, game_update, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}

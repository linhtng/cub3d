/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:22:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/29 16:47:15 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	key_press(int key_code, t_cubed_bonus *cubed)
{
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
	if (key_code == INTERACT)
		cubed->keys[SPACE_BAR] = 1;
	cubed->key_pressed = key_code;
	return (0);
}

int	key_release(int key_code, t_cubed_bonus *cubed)
{
	if (key_code == ESC)
		mlx_close((t_cubed *)cubed, 0, "Normal exit");
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
	return (0);
}

void	update_animation(t_cubed_bonus *cubed, t_scene_bonus *scene)
{
	if (cubed->animated_frame == ANIMATION_FRAME)
	{
		scene->bonus_textures[2] = scene->bonus_ceiling[1];
		redraw((t_cubed *)cubed);
		refresh_images((t_cubed *)cubed);
	}
	if (cubed->animated_frame == ANIMATION_FRAME * 2)
	{
		scene->bonus_textures[2] = scene->bonus_ceiling[2];
		redraw((t_cubed *)cubed);
		refresh_images((t_cubed *)cubed);
	}
	else if (cubed->animated_frame == ANIMATION_FRAME * 3)
	{
		scene->bonus_textures[2] = scene->bonus_ceiling[0];
		redraw((t_cubed *)cubed);
		refresh_images((t_cubed *)cubed);
		cubed->animated_frame = 0;
	}
}

int	game_update(void *param)
{
	t_cubed_bonus	*cubed;
	t_scene_bonus	*scene;

	cubed = (t_cubed_bonus *)param;
	scene = (t_scene_bonus *)cubed->scene;
	cubed->animated_frame++;
	update_animation(cubed, scene);
	handle_press_bonus(param);
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
	refresh_images(cubed);
	mlx_hook(cubed->window, 17, 0, close_window, cubed);
	mlx_hook(cubed->window, 2, 1L << 0, key_press, cubed);
	mlx_hook(cubed->window, 3, 1L << 1, key_release, cubed);
	mlx_hook(cubed->window, 6, 1L << 6, mouse_move, cubed);
	mlx_loop_hook(cubed->mlx, game_update, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}

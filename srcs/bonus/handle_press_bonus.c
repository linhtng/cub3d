/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/24 16:36:16 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	close_window(t_cubed *cubed)
{
	mlx_close(cubed, 0, "normal exit");
	return (0);
}

int	handle_press_bonus(int key_code, t_cubed *param)
{
	t_cubed_bonus	*cubed;

	cubed = (t_cubed_bonus *)param;
	if (cubed->keys[LEFT_PRESSED] || cubed->keys[RIGHT_PRESSED])
		turn_player(param, key_code);
	if (cubed->keys[W_PRESSED] || cubed->keys[S_PRESSED])
	{
		move_forward_backward(param, key_code);
	}
	if (cubed->keys[A_PRESSED] || cubed->keys[D_PRESSED])
	{
		move_right_left(param, key_code);
	}
	else if (cubed->keys[SPACE_BAR])
		check_interaction((t_cubed_bonus *)cubed);
	if (cubed->dirty_images)
		refresh_images(param);
	return (0);
}

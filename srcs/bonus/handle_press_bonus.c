/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/29 16:45:30 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	close_window(t_cubed *cubed)
{
	mlx_close(cubed, 0, "normal exit");
	return (0);
}

int	handle_press_bonus(t_cubed *param)
{
	t_cubed_bonus	*cubed;

	cubed = (t_cubed_bonus *)param;
	if (cubed->keys[LEFT_PRESSED])
		turn_player(param, TURN_LEFT);
	if (cubed->keys[RIGHT_PRESSED])
		turn_player(param, TURN_RIGHT);
	if (cubed->keys[W_PRESSED])
		move_forward_backward(param, FORWARD);
	if (cubed->keys[S_PRESSED])
		move_forward_backward(param, BACK);
	if (cubed->keys[A_PRESSED])
		move_right_left(param, LEFT);
	if (cubed->keys[D_PRESSED])
		move_right_left(param, RIGHT);
	else if (cubed->keys[SPACE_BAR])
		check_interaction((t_cubed_bonus *)cubed);
	if (cubed->dirty_images)
		refresh_images(param);
	return (0);
}

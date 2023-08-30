/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 16:57:58 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * close_window() closes the window if the red  x is pressed. It calls 
 * mlx_close() with an exit code of 0 for a normal exit.
*/
int	close_window(t_cubed *cubed)
{
	mlx_close(cubed, 0, "normal exit");
	return (0);
}

/*
 * handle_press() checks if any program keys are pressed and calls the
 * appropriate function to handle the key press. If the images are dirty, it
 * calls refresh_images() to refresh the images.
*/
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
	if (cubed->keys[SPACE_BAR])
		check_interaction((t_cubed_bonus *)cubed);
	if (cubed->dirty_images)
		refresh_images(param);
	return (0);
}

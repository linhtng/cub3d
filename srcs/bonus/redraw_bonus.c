/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:14:09 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 18:48:53 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	redraw(t_cubed *cubed)
{
	// ((t_cubed_bonus *)cubed)->reward.animated_frame++;
	// if (((t_cubed_bonus *)cubed)->reward.animated_frame == ANIMATION_FRAME)
	// 	((t_cubed_bonus *)cubed)->reward.pos.y += 10;
	// else if (((t_cubed_bonus *)cubed)->reward.animated_frame == ANIMATION_FRAME * 2)
	// {
	// 	((t_cubed_bonus *)cubed)->reward.pos.y -= 10;
	// 	((t_cubed_bonus *)cubed)->reward.animated_frame = 0;
	// }
	ft_memset(((t_cubed_bonus *)cubed)->mini_player_img->addr, TRANSPARENT, \
	MINI_MAP_DIAMETER * MINI_MAP_DIAMETER * \
	(((t_cubed_bonus *)cubed)->mini_player_img->bits_per_pixel / 8));
	ft_memset(cubed->raycast_info->r_img->addr, TRANSPARENT, \
	PROJECTION_WIDTH * PROJECTION_HEIGHT * \
	(cubed->raycast_info->r_img->bits_per_pixel / 8));
	cast_rays(cubed);
	draw_minimap(cubed);
	//printf("[animate reward] FRAME: %d, pos y: %f, pos x: %f\n", ((t_cubed_bonus *)cubed)->reward.animated_frame, ((t_cubed_bonus *)cubed)->reward.pos.y, ((t_cubed_bonus *)cubed)->reward.pos.x);
	//mlx_put_image_to_window(cubed->mlx, cubed->window, 
	//((t_cubed_bonus *)cubed)->reward_img->img,((t_cubed_bonus *)cubed)->reward.pos.y, ((t_cubed_bonus *)cubed)->reward.pos.x);
}

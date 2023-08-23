/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:14:09 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/23 19:20:19 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	redraw(t_cubed *cubed)
{
	ft_memset(((t_cubed_bonus *)cubed)->mini_player_img->addr, TRANSPARENT, \
	MINI_MAP_DIAMETER * MINI_MAP_DIAMETER * \
	(((t_cubed_bonus *)cubed)->mini_player_img->bits_per_pixel / 8));
	ft_memset(cubed->raycast_info->r_img->addr, TRANSPARENT, \
	PROJECTION_WIDTH * PROJECTION_HEIGHT * \
	(cubed->raycast_info->r_img->bits_per_pixel / 8));
	cast_rays(cubed);
	draw_minimap(cubed);
}

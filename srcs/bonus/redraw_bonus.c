/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:14:09 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 14:48:29 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast_bonus.h"
#include "cub3D_bonus.h"

void	redraw(t_cubed *cubed)
{
	ft_memset(cubed->mini_player_img->addr, TRANSPARENT, \
	WIN_WIDTH * WIN_HEIGHT * (cubed->mini_player_img->bits_per_pixel / 8));
	cubed->scene->player.location.color = 0x000FFF;//
	ft_memset(cubed->raycast_info->r_img->addr, TRANSPARENT, \
	PROJECTION_WIDTH * PROJECTION_HEIGHT * \
	(cubed->raycast_info->r_img->bits_per_pixel / 8));
	cast_rays(cubed);
	draw_mini_player(cubed);
}

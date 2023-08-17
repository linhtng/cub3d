/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:50:41 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 14:40:22 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

//TODO move to bonus entire file
static void	draw_nose(t_cubed *cubed)
{
	t_vector	temp;

	temp.x = cubed->scene->player.location.x + cubed->scene->player.d.x  * 5;
	temp.y = cubed->scene->player.location.y + cubed->scene->player.d.y * 5;
	temp.color = 0xff00f3;
	ft_bresenham(temp, cubed->scene->player.location, ((t_cubed_bonus *)cubed)->mini_player_img);
}

void	draw_mini_player(t_cubed *cubed)
{
	// ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	my_put_square(((t_cubed_bonus *)cubed)->mini_player_img, cubed->scene->player.location, 10);
	draw_nose(cubed);
}

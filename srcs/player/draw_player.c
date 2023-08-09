/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:50:41 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 13:34:07 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

static void	draw_nose(t_cubed *cubed)
{
	t_vector temp;
	
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	temp.color = 0xff00f3;
	ft_bresenham(temp, cubed->player.location, cubed->mini_player_img);
}
void	draw_mini_player(t_cubed *cubed)
{
	// ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	my_put_square(cubed->mini_player_img, cubed->player.location, 10);
	draw_nose(cubed);
}

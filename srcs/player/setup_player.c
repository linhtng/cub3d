/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:12:52 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 10:50:30 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

void	setup_player(t_cubed *cubed, int i, int j, char dir)
{
	t_vector temp;
	t_vector start;

	start.x  = 0;
	start.y = 0;
	start.color = 0x00;
	cubed->player.location.y = i * CELL_SIZE + CELL_SIZE / 2;
	cubed->player.location.x = j * CELL_SIZE + CELL_SIZE / 2;
	cubed->player.location.color = 0xFFFF00;//yellow
	if (dir == 'N')
		cubed->player.angle = 90.0f;
	if (dir == 'S')
		cubed->player.angle = 270.0f;
	if (dir == 'E')
		cubed->player.angle = 0.0f;
	if (dir == 'W')
		cubed->player.angle = 180.0f;
	cubed->player.d.x = cos(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.d.y = -sin(deg_to_rad(cubed->player.angle)) * 5;
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	my_put_square(cubed->player_img, cubed->player.location, 10);
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);//drawing the 'nose' not correct...
}

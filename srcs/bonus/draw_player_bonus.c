/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:50:41 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/21 12:44:43 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_nose(t_cubed_bonus *cubed, t_vector *mini_player)
{
	t_vector	temp;

	temp.x = (int)mini_player->x + cubed->scene->player.d.x * 2;
	temp.y = (int)mini_player->y + cubed->scene->player.d.y * 2;
	temp.color = LIGHT_GREY;
	ft_bresenham_clipped(temp, *mini_player, cubed->mini_player_img);
}

void	draw_mini_player(t_cubed *cubed)
{
	t_vector	mini_player;

	mini_player.x = MINI_MAP_RADIUS;
	mini_player.y = MINI_MAP_RADIUS;
	mini_player.color = RED;
	my_put_rectangle(((t_cubed_bonus *)cubed)->mini_player_img, \
	mini_player, 5, 5);
	draw_nose((t_cubed_bonus *)cubed, &mini_player);
}

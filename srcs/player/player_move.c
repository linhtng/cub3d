/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:43:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 11:09:47 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

	// printf("PLAYER ANGLE: %f\n", cubed->player.angle);//
void	turn_player(t_cubed *cubed, int key_code)
{
	if (key_code == TURN_LEFT)
		cubed->player.angle = correct_degrees(cubed->player.angle + 5);//turn 5 deg at a time
	else
		cubed->player.angle = correct_degrees(cubed->player.angle - 5);//turn 5 deg at a time	
	cubed->player.d.x = cos(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.d.y = -sin(deg_to_rad(cubed->player.angle)) * 5;
	//redraw
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	cast_rays(cubed);
	draw_mini_player(cubed);
	cubed->dirty_images = TRUE;
}

void	move_forward(t_cubed *cubed)
{
	//change player coords acording to the player delta x and y
	cubed->player.location.x += cubed->player.d.x;
	cubed->player.location.y += cubed->player.d.y;
	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	//draw the new view
	cast_rays(cubed);
	//draw player and nose
	draw_mini_player(cubed);
	cubed->dirty_images = TRUE;
}
void	move_backward(t_cubed *cubed)
{
	//change player coords acording to the player delta x and y
	cubed->player.location.x -= cubed->player.d.x;
	cubed->player.location.y -= cubed->player.d.y;
	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	//draw the new view
	cast_rays(cubed);
	//draw player and nose
	draw_mini_player(cubed);
	//refresh all images
	cubed->dirty_images = TRUE;
}

void	move_right(t_cubed *cubed)
{
	float		move_angle;

	move_angle = correct_degrees(cubed->player.angle - 90.0f);
	//change player coords acording to the player delta x and y
	cubed->player.location.x += cos(deg_to_rad(move_angle)) * 5;
	cubed->player.location.y += -sin(deg_to_rad(move_angle)) * 5;
	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	cast_rays(cubed);
	draw_mini_player(cubed);
	cubed->dirty_images = TRUE;
}

void	move_left(t_cubed *cubed)
{
	float		move_angle;

	move_angle = correct_degrees(cubed->player.angle + 90.0f);
	//change player coords acording to the player delta x and y
	cubed->player.location.x += cos(deg_to_rad(move_angle)) * 5;
	cubed->player.location.y += -sin(deg_to_rad(move_angle)) * 5;
	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	cast_rays(cubed);
	draw_mini_player(cubed);
	cubed->dirty_images = TRUE;
}
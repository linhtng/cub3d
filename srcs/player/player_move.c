/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:43:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/06 20:44:06 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "libft.h"
#include "cub3D.h"

void	turn_player(t_cubed *cubed, int key_code)
{
	t_vector temp;
	printf("player should look some direction...\n");
	
	if (key_code == TURN_LEFT)
	{
		cubed->player.angle = correct_degrees(cubed->player.angle + 1);//turn 5 deg at a time
	}
	else
	{
		cubed->player.angle = correct_degrees(cubed->player.angle - 1);//turn 5 deg at a time	
	}
	cubed->player.d.x = cos(deg_to_rad(cubed->player.angle)) * 5;
	cubed->player.d.y = -sin(deg_to_rad(cubed->player.angle)) * 5;
	//redraw
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	my_put_square(cubed->player_img, cubed->player.location, 10);
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	printf("PLAYER ANGLE: %f\n", cubed->player.angle);//
	cast_rays(cubed);
	cubed->player.location.color = 0xFFFFFF;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
	refresh_images(cubed);
}

void	move_forward(t_cubed *cubed)
{
	t_vector temp; //for nose

	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	//change player coords acording to the player delta x and y
	cubed->player.location.x += cubed->player.d.x;
	cubed->player.location.y += cubed->player.d.y;
	//draw the new view
	cast_rays(cubed);
	//draw player and nose
	my_put_square(cubed->player_img, cubed->player.location, 10);//player
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;//nose setup
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
	//refresh all images
	refresh_images(cubed);
}
void	move_backward(t_cubed *cubed)
{
	t_vector temp; //for nose

	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	//change player coords acording to the player delta x and y
	cubed->player.location.x -= cubed->player.d.x;
	cubed->player.location.y -= cubed->player.d.y;
	//draw the new view
	cast_rays(cubed);
	//draw player and nose
	my_put_square(cubed->player_img, cubed->player.location, 10);//player
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;//nose setup
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
	//refresh all images
	refresh_images(cubed);
}

void	move_right(t_cubed *cubed)
{
	t_vector	temp; //for nose
	float		move_angle;

	move_angle = correct_degrees(cubed->player.angle - 90.0f);
	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	//change player coords acording to the player delta x and y
	printf("PLAYER POSTION MV RIGHT before: %f , %f\n", cubed->player.location.x, cubed->player.location.y);
	cubed->player.location.x += cos(deg_to_rad(move_angle)) * 5;
	cubed->player.location.y += -sin(deg_to_rad(move_angle)) * 5;
	printf("PLAYER POSTION MV RIGHT after: %f , %f\n", cubed->player.location.x, cubed->player.location.y);
	//draw the new view
	cast_rays(cubed);
	//draw player and nose
	my_put_square(cubed->player_img, cubed->player.location, 10);//player
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;//nose setup
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
	//refresh all images
	refresh_images(cubed);
}

void	move_left(t_cubed *cubed)
{
	t_vector	temp; //for nose
	float		move_angle;

	move_angle = correct_degrees(cubed->player.angle + 90.0f);
	//clear player minimap image
	ft_memset(cubed->player_img->addr, 0x00ffffff, WIN_WIDTH * WIN_HEIGHT * (cubed->player_img->bits_per_pixel / 8));
	//change player coords acording to the player delta x and y
	printf("PLAYER POSTION MV RIGHT before: %f , %f\n", cubed->player.location.x, cubed->player.location.y);
	cubed->player.location.x += cos(deg_to_rad(move_angle)) * 5;
	cubed->player.location.y += -sin(deg_to_rad(move_angle)) * 5;
	printf("PLAYER POSTION MV RIGHT after: %f , %f\n", cubed->player.location.x, cubed->player.location.y);
	//draw the new view
	cast_rays(cubed);
	//draw player and nose
	my_put_square(cubed->player_img, cubed->player.location, 10);//player
	temp.x = cubed->player.location.x + cubed->player.d.x  * 5;//nose setup
	temp.y = cubed->player.location.y + cubed->player.d.y * 5;
	ft_bresenham(cubed->player.location, temp, cubed->player_img);
	//refresh all images
	refresh_images(cubed);
}
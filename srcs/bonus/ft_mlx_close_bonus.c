/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_close_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:24:40 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 17:58:30 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_raycast_bonus.h"
// #include "cub3D_bonus.h"
#include "cub3D.h"

//TODO destroy and free all images and other allocated stuffs
int	mlx_close(t_cubed *cubed, int exit_code, char *exit_msg)
{
	printf("MLX should close...\n");
	// if (cubed->img) //saying this double frees????wtf
	// {
	// 	mlx_destroy_image(cubed->mlx, cubed->img->img);
	// 	free(cubed->img);
	// }
	// if (cubed->player_img)
	// {
	// 	mlx_destroy_image(cubed->mlx, cubed->player_img->img);
	// 	free(cubed->player_img);
	// }
	if (cubed->window)
	{
		mlx_destroy_window(cubed->mlx, cubed->window);
		cubed->window = NULL;
	}
	if (cubed->mlx)
		cubed->mlx = NULL;
	//write exit message prn
	write(2, exit_msg ,1);//
	free_scene_data(cubed->scene);
	exit(exit_code);
	return (0);
}
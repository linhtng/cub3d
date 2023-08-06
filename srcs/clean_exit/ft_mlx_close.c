/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:24:40 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/28 11:00:27 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"

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
	exit(exit_code);
	return (0);
}
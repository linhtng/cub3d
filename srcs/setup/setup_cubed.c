/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cubed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:34:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 16:14:36 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * zero_cubed() zeros all the values in the cubed struct.
 */
static void	zero_cubed(t_cubed *cubed)
{
	cubed->mlx = NULL;
	cubed->window = NULL;
	cubed->dirty_images = 0;
	cubed->raycast_info = NULL;
	cubed->scene = NULL;
}

/*
 * setup_cubed() initializes the cubed struct and calls mlx_init() and
 * mlx_new_window() to initialize the mlx and window.
 */
void	setup_cubed(t_cubed *cubed)
{
	zero_cubed(cubed);
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		mlx_close(cubed, 1, "intialization of mlx failed");
	cubed->window = mlx_new_window(cubed->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cubed->window)
		mlx_close(cubed, 1, "intialization of mlx window failed");
}

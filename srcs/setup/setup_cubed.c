/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cubed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:34:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 12:48:24 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

void	setup_cubed(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->window = mlx_new_window(cubed->mlx, WIN_WIDTH, WIN_HEIGHT,"my minimap");
	cubed->minimap_img = get_new_image(cubed, WIN_WIDTH, WIN_HEIGHT);
	cubed->player_img = get_new_image(cubed, WIN_WIDTH, WIN_HEIGHT);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cubed_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:34:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 14:48:24 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast_bonus.h"
#include "cub3D_bonus.h"

void	setup_cubed(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->window = mlx_new_window(cubed->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	cubed->minimap_img = get_new_image(cubed, WIN_WIDTH, WIN_HEIGHT);
	cubed->mini_player_img = get_new_image(cubed, WIN_WIDTH, WIN_HEIGHT);
}

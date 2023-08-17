/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cubed_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:34:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 15:56:44 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "cub3D.h"

void	setup_cubed(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->window = mlx_new_window(cubed->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	((t_cubed_bonus *)cubed)->minimap_img = get_new_image(cubed, WIN_WIDTH, WIN_HEIGHT);
	((t_cubed_bonus *)cubed)->mini_player_img = get_new_image(cubed, WIN_WIDTH, WIN_HEIGHT);
	((t_cubed_bonus *)cubed)->frame_img = get_new_xpm_image(cubed, "textures/cub3d_tex/cubed_frame_noshade.xpm");
}

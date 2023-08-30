/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:14:09 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 15:55:03 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * redraw() zeros the raycasting image and calls cast_rays() to draw the new 
 * view.
*/
void	redraw(t_cubed *cubed)
{
	ft_memset(cubed->raycast_info->r_img->addr, TRANSPARENT, \
	PROJECTION_WIDTH * PROJECTION_HEIGHT * \
	(cubed->raycast_info->r_img->bits_per_pixel / 8));
	cast_rays(cubed);
}

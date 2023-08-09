/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:18:06 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 13:20:13 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

void	setup_raycast(t_cubed *cubed, t_raycast *raycast_info)
{
	raycast_info->r_img = get_new_image(cubed, PROJECTION_WIDTH, PROJECTION_HEIGHT);
	raycast_info->background_img = get_new_image(cubed, PROJECTION_WIDTH, PROJECTION_HEIGHT);
	raycast_info->angle_between_rays = (float) FOV / (float) PROJECTION_WIDTH;
	raycast_info->center_of_projection.x = PROJECTION_WIDTH / 2;
	raycast_info->center_of_projection.y = PROJECTION_HEIGHT / 2;
	cubed->raycast_info = raycast_info;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:18:06 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 19:04:30 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

//only need to do once in the begining reuse the background as lonng as we dont raycast anything to it
void	draw_background(t_cubed *cubed)
{
	t_vector start;

	start.x = 0;
	start.y = 0;
	start.color = cubed->scene->elems.ceiling_color;
	while ((int) start.y < PROJECTION_HEIGHT)
	{
		if ((int) start.y > PROJECTION_HEIGHT / 2)
			start.color = cubed->scene->elems.floor_color;
		my_put_line_h(cubed->raycast_info->background_img, &start, PROJECTION_WIDTH);
		(start.y)++;
	}
}
void	setup_raycast(t_cubed *cubed, t_raycast *raycast_info)
{
	raycast_info->r_img = get_new_image(cubed, PROJECTION_WIDTH, PROJECTION_HEIGHT);
	raycast_info->background_img = get_new_image(cubed, PROJECTION_WIDTH, PROJECTION_HEIGHT);
	raycast_info->angle_between_rays = (float) FOV / (float) PROJECTION_WIDTH;
	raycast_info->center_of_projection.x = PROJECTION_WIDTH / 2;
	raycast_info->center_of_projection.y = PROJECTION_HEIGHT / 2;
	cubed->raycast_info = raycast_info;
}
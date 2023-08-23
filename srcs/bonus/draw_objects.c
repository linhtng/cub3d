/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:55:46 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/23 15:50:28 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static t_vector	get_tex_vec(t_vector *hit, float y_step, \
float line_size)
{
	t_vector	texture;

	texture.y = 0;
	if (line_size > PROJECTION_HEIGHT)
		texture.y = ((line_size - PROJECTION_HEIGHT) / 2.0f) * y_step;
	// if (dir == NORTH)
		texture.x = TEXTURE_SIZE - 1 - (((int) hit->x) % TEXTURE_SIZE);
	// else if (dir == SOUTH)
	// 	texture.x = ((int) hit->x) % TEXTURE_SIZE;
	// else if (dir == EAST)
	// 	texture.x = TEXTURE_SIZE - 1 - (((int) hit->y) % TEXTURE_SIZE);
	// else
	// 	texture.x = ((int) hit->y) % TEXTURE_SIZE;
	return (texture);
}
static void	clip_line_height(t_draw_info *d_info)
{
	if (d_info->height > PROJECTION_HEIGHT)
		d_info->height = PROJECTION_HEIGHT;
	else
		d_info->height = round(d_info->height);
}

void	draw_object(t_cubed *cubed_given, int x)
{
	//how big to draw the object
	//get what color to draw from the texture
	//get initial x value of the texture to draw from based on draw height and y_step
	//scaling object size
	t_draw_info	    draw_info;
    int             index;
    unsigned int	color;
    t_cubed_bonus   *cubed;

	cubed = (t_cubed_bonus *) cubed_given;
    draw_info.height = CELL_SIZE / cubed->reward.distance;
    printf("[draw obj] height: %f, reward distance: %f\n", draw_info.height, cubed->reward.distance);
    draw_info.project_x = x;
	draw_info.project_y = (PROJECTION_HEIGHT - draw_info.height) / 2;
    draw_info.y_step = TEXTURE_SIZE / draw_info.height;
    draw_info.tex = get_tex_vec(&cubed->reward.map_coor, draw_info.y_step, draw_info.height);
    clip_line_height(&draw_info);
    index = 0;
    while (index++ < draw_info.height)
    {
        color = ft_pixel_get(cubed->reward_img, \
		draw_info.tex.x, draw_info.tex.y);
		ft_pixel_put(cubed->raycast_info->r_img, \
		draw_info.project_x, draw_info.project_y, color);
		draw_info.project_y++;
		draw_info.tex.y += draw_info.y_step;
    }
}

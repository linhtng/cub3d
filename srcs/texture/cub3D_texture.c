/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/22 16:11:35 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	ft_pixel_get(t_img_data *data, int x, int y)
{
	unsigned int	dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
		return (0XFF0000);
	dst = *(unsigned int *)(data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8)));
	return (dst);
}

void	load_texture(t_scene *scene, t_cubed *cubed)
{
	scene->texture[NORTH] = get_new_xpm_image(cubed, scene->elems.north);
	scene->texture[SOUTH] = get_new_xpm_image(cubed, scene->elems.south);
	scene->texture[EAST] = get_new_xpm_image(cubed, scene->elems.east);
	scene->texture[WEST] = get_new_xpm_image(cubed, scene->elems.west);
}

t_vector	get_texture_vec(t_vector *hit, int dir, float y_step, \
float line_size)
{
	t_vector	texture;

	texture.y = 0;
	if (line_size > PROJECTION_HEIGHT)
		texture.y = ((line_size - PROJECTION_HEIGHT) / 2.0f) * y_step;
	if (dir == NORTH)
		texture.x = TEXTURE_SIZE - 1 - (((int) hit->x) % TEXTURE_SIZE);
	else if (dir == SOUTH)
		texture.x = ((int) hit->x) % TEXTURE_SIZE;
	else if (dir == EAST)
		texture.x = TEXTURE_SIZE - 1 - (((int) hit->y) % TEXTURE_SIZE);
	else
		texture.x = ((int) hit->y) % TEXTURE_SIZE;
	return (texture);
}

static float	clip_line_height(float to_clip)
{
	float	line_height;

	if (to_clip > PROJECTION_HEIGHT)
		line_height = PROJECTION_HEIGHT;
	else
		line_height = round(to_clip);
	return (line_height);
}

void	draw_textured_walls(t_cubed *cubed, int project_x, t_ray_calc *ray, \
int dir)
{
	float			line_height;
	unsigned int	pane_y_color[2];
	float			y_step;
	t_vector		texture;
	int				index;

	line_height = CELL_SIZE * PROJECTION_HEIGHT / ray->distance;
	y_step = TEXTURE_SIZE / line_height;
	if (ray->shortest == 'v')
		texture = get_texture_vec(&ray->v_map, dir, y_step, line_height);
	else
		texture = get_texture_vec(&ray->h_map, dir, y_step, line_height);
	line_height = clip_line_height(line_height);
	pane_y_color[0] = (PROJECTION_HEIGHT - line_height) / 2;
	index = 0;
	while (index++ < line_height)
	{
		pane_y_color[1] = ft_pixel_get(cubed->scene->texture[dir], \
		texture.x, texture.y);
		ft_pixel_put(cubed->raycast_info->r_img, project_x, \
		pane_y_color[0], pane_y_color[1]);
		pane_y_color[0]++;
		texture.y += y_step;
	}
}

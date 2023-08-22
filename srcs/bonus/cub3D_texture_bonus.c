/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/22 11:55:09 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_pixel_put(t_img_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_pixel_get(t_img_data *data, int x, int y)
{
	unsigned int	dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
	{
		// printf("[FT PIXEL GET] Out of bounds: x %ii, y %i \n", x, y);//
		return (RED);
	}
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
	if (texture.x >= 64 || texture.x < 0 || texture.y >= 64 || texture.y < 0)//
		printf("[GET TEXTURE VEC] tex.x %f, tex.y %f \n", texture.x, texture.y);//
	return (texture);
}

void	b_draw_textured_walls(t_cubed *cubed, t_ray_calc *ray, t_draw_info *d_info)
{
	t_vector	pane;
	float		y_step;
	int			index;

	y_step = TEXTURE_SIZE / d_info->line_height;
	if (ray->shortest == 'v')
		d_info->texture = get_texture_vec(&ray->v_map, d_info->dir, y_step, d_info->line_height);
	else
		d_info->texture = get_texture_vec(&ray->h_map, d_info->dir, y_step, d_info->line_height);
	if (d_info->line_height > PROJECTION_HEIGHT)
		d_info->line_height = PROJECTION_HEIGHT;
	pane.y = cubed->raycast_info->center_of_projection.y - d_info->line_height / 2;
	index = 0;
	while (index < d_info->line_height)
	{
		pane.color = ft_pixel_get(cubed->scene->texture[d_info->dir], \
		d_info->texture.x, d_info->texture.y);
		ft_pixel_put(cubed->raycast_info->r_img, d_info->project_x, pane.y, pane.color);
		index++;
		pane.y++;
		d_info->texture.y += y_step;
	}
}

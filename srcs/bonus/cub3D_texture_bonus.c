/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/21 14:08:16 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void draw_floors(t_cubed *cubed, t_ray_calc *ray, float line_height)
{
	t_vector	tex;
	float		delta_y;
	float		ray_fix;
	
	if (line_height == PROJECTION_HEIGHT)
		return ;
	tex.y = cubed->raycast_info->center_of_projection.y - line_height / 2 + line_height;
	delta_y = tex.y - cubed->raycast_info->center_of_projection.y - line_height / 2 - PROJECTION_HEIGHT / 2.0f;
	ray_fix = cos(deg_to_rad(correct_degrees(cubed->scene->player.angle - ray->angle)));
	while (tex.y < PROJECTION_HEIGHT)
	{
		tex.x = cubed->scene->player.location.x / 2 + cos(deg_to_rad(ray->angle)) * (PROJECTION_HEIGHT / 2 - 2) / delta_y / ray_fix;
	}
}

void	draw_textured_walls(t_cubed *cubed, int project_x, t_ray_calc *ray, \
int dir)
{
	float		line_height;
	t_vector	pane;
	float		y_step;
	t_vector	texture;
	int			index;

	line_height = CELL_SIZE * PROJECTION_HEIGHT / ray->distance;
	y_step = TEXTURE_SIZE / line_height;
	if (ray->shortest == 'v')
		texture = get_texture_vec(&ray->v_map, dir, y_step, line_height);
	else
		texture = get_texture_vec(&ray->h_map, dir, y_step, line_height);
	if (line_height > PROJECTION_HEIGHT)
		line_height = PROJECTION_HEIGHT;
	pane.y = cubed->raycast_info->center_of_projection.y - line_height / 2;
	index = 0;
	while (index < line_height)
	{
		pane.color = ft_pixel_get(cubed->scene->texture[dir], \
		texture.x, texture.y);
		ft_pixel_put(cubed->raycast_info->r_img, project_x, pane.y, pane.color);
		index++;
		pane.y++;
		texture.y += y_step;
	}
}

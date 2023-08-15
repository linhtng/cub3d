/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/15 11:08:12 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
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

unsigned int	mlx_pixel_get(t_img_data *data, int x, int y)
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
	scene->dir[NORTH] = get_new_xpm_image(cubed, scene->elems.north);
	scene->dir[SOUTH] = get_new_xpm_image(cubed, scene->elems.south);
	scene->dir[EAST] = get_new_xpm_image(cubed, scene->elems.east);
	scene->dir[WEST] = get_new_xpm_image(cubed, scene->elems.west);
}

/*TODO check if x is flipped the right way 
	(test with a non-symmentric texture for example)
	- north and east are flipped currently
	- TEXTURE SIZE minus the calc x -2 corrects (why -2????)
*/
t_vector	get_texture_vec(t_vector *hit, int dir, float y_step, \
float line_size)
{
	t_vector	texture;

	texture.y = 0;
	if (line_size > PROJECTION_HEIGHT)
		texture.y = ((line_size - PROJECTION_HEIGHT) / 2.0f) * y_step;
	if (dir == NORTH)
		texture.x = TEXTURE_SIZE - 2 - (((int) hit->x * 2) % TEXTURE_SIZE);
	else if (dir == SOUTH)
		texture.x = ((int) hit->x * 2) % TEXTURE_SIZE;
	else if (dir == EAST)
		texture.x = TEXTURE_SIZE - 2 - (((int) hit->y * 2) % TEXTURE_SIZE);
	else
		texture.x = ((int) hit->y * 2) % TEXTURE_SIZE;
	return (texture);
}

void	draw_textured_walls(t_cubed *cubed, int x, t_ray_calc *ray, int dir)
{
	float		line_height;
	t_vector	start;
	float		y_step;
	t_vector	texture_vec;
	int			index;

	line_height = CELL_SIZE * PROJECTION_HEIGHT / ray->distance;
	y_step = TEXTURE_SIZE / line_height;
	if (ray->shortest == 'v')
		texture_vec = get_texture_vec(&ray->v_map, dir, y_step, line_height);
	else
		texture_vec = get_texture_vec(&ray->h_map, dir, y_step, line_height);
	if (line_height > PROJECTION_HEIGHT)
		line_height = PROJECTION_HEIGHT;
	start.x = x;
	start.y = cubed->raycast_info->center_of_projection.y - line_height / 2;
	index = 0;
	while (index < line_height)
	{
		start.color = mlx_pixel_get(cubed->scene->dir[dir], texture_vec.x, texture_vec.y);
		ft_pixel_put(cubed->raycast_info->r_img, start.x, start.y, start.color);
		index++;
		start.y++;
		texture_vec.y += y_step;
	}
}

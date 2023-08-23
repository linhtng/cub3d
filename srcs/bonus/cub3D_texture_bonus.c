/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/23 19:19:05 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

unsigned int	ft_pixel_get(t_img_data *data, int x, int y)
{
	unsigned int	dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
		return (RED);
	dst = *(unsigned int *)(data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8)));
	return (dst);
}

void	load_texture(t_scene *normal_scene, t_cubed *cubed)
{
	t_scene_bonus	*scene;

	scene = (t_scene_bonus *)normal_scene;
	scene->texture[NORTH] = get_new_xpm_image(cubed, scene->elems.north);
	scene->texture[SOUTH] = get_new_xpm_image(cubed, scene->elems.south);
	scene->texture[EAST] = get_new_xpm_image(cubed, scene->elems.east);
	scene->texture[WEST] = get_new_xpm_image(cubed, scene->elems.west);
	scene->bonus_textures[0] = \
	get_new_xpm_image(cubed, scene->bonus_elems.door);
	scene->bonus_textures[1] = \
	get_new_xpm_image(cubed, scene->bonus_elems.floor);
	scene->bonus_textures[2] = \
	get_new_xpm_image(cubed, scene->bonus_elems.ceiling);
}

static t_vector	get_tex_vec(t_vector *hit, int dir, float y_step, \
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

static void	clip_line_height(t_draw_info *d_info)
{
	if (d_info->height > PROJECTION_HEIGHT)
		d_info->height = PROJECTION_HEIGHT;
	else
		d_info->height = round(d_info->height);
}

static unsigned int	choose_from_texture(t_scene *scene, t_draw_info *draw)
{
	unsigned int	color;

	if (draw->material_hit == DOOR_CLOSED)
	{
		color = ft_pixel_get(((t_scene_bonus *)scene)->bonus_textures[0], \
		draw->tex.x, draw->tex.y);
	}
	else
	{
		color = \
		ft_pixel_get(scene->texture[draw->dir], draw->tex.x, draw->tex.y);
	}
	return (color);
}

void	b_draw_textured_walls(t_cubed *cubed, t_ray_calc *ray, \
t_draw_info *draw)
{
	unsigned int	color;
	float			y_step;
	int				index;

	y_step = TEXTURE_SIZE / draw->height;
	if (ray->shortest == 'v')
		draw->tex = get_tex_vec(&ray->v_map, draw->dir, y_step, draw->height);
	else
		draw->tex = get_tex_vec(&ray->h_map, draw->dir, y_step, draw->height);
	clip_line_height(draw);
	draw->project_y = (PROJECTION_HEIGHT - draw->height) / 2;
	index = 0;
	while (index++ < draw->height)
	{
		color = choose_from_texture(cubed->scene, draw);
		ft_pixel_put(cubed->raycast_info->r_img, \
		draw->project_x, draw->project_y, color);
		draw->project_y++;
		draw->tex.y += y_step;
	}
}

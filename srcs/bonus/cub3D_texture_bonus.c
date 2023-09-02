/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/09/02 16:17:06 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * load_texture() loads all textures from the xpm files and stores them in the
 * scene structure.
*/
void	load_texture(t_scene *normal_scene, t_cubed *cubed)
{
	t_scene_bonus	*scene;

	scene = (t_scene_bonus *)normal_scene;
	scene->texture[NORTH] = get_new_xpm_image(cubed, scene->elems.north);
	scene->texture[SOUTH] = get_new_xpm_image(cubed, scene->elems.south);
	scene->texture[EAST] = get_new_xpm_image(cubed, scene->elems.east);
	scene->texture[WEST] = get_new_xpm_image(cubed, scene->elems.west);
	scene->bonus_textures[0] = 
		get_new_xpm_image(cubed, scene->bonus_elems.door);
	scene->bonus_textures[1] = 
		get_new_xpm_image(cubed, scene->bonus_elems.floor);
	scene->bonus_ceiling[0] = 
		get_new_xpm_image(cubed, scene->bonus_elems.ceiling[0]);
	scene->bonus_ceiling[1] = 
		get_new_xpm_image(cubed, scene->bonus_elems.ceiling[1]);
	scene->bonus_ceiling[2] = 
		get_new_xpm_image(cubed, scene->bonus_elems.ceiling[2]);
	scene->bonus_textures[2] = scene->bonus_ceiling[0];
}

/*
 * get_texture_vec() calculates the texture vector for the raycasted vertical 
 * stripe of wall. The y is calulated by the difference, if any, between the 
 * line size and the projection height. The x is calculated by the direction 
 * of the ray and the position of the hit. 
*/
static t_vector	get_tex_vec(t_vector *hit, int dir, double y_step, 
double line_size)
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

/*
 * clip_line_height() clips the line height to the projection height if the
 * line height is greater than the projection height. Otherwise, it rounds the
 * line height to the nearest integer.
*/
static void	clip_line_height(t_draw_info *d_info)
{
	if (d_info->height > PROJECTION_HEIGHT)
		d_info->height = PROJECTION_HEIGHT;
	else
		d_info->height = round(d_info->height);
}

/*
 * choose_from_texture() chooses the color from the texture based on the 
 * direction of the ray and if the material hit is a door or not.
*/
static unsigned int	choose_from_texture(t_scene *scene, t_draw_info *draw)
{
	unsigned int	color;

	if (draw->material_hit == DOOR_CLOSED)
	{
		color = ft_pixel_get(((t_scene_bonus *)scene)->bonus_textures[0], 
				draw->tex.x, draw->tex.y);
	}
	else
	{
		if (!scene->texture[draw->dir])
			printf("choose_from texture, draw dir: %d\n", draw->dir);
		color = 
			ft_pixel_get(scene->texture[draw->dir], draw->tex.x, draw->tex.y);
	}
	return (color);
}

/*
 * b_draw_textured_walls() draws the textured walls based on the direction of the
 * ray and the position of the hit.
 * y_step = the texture size and the line height and determines how quicly the
 * texture is traversed.
 * The color to be drawn is selected from the appropriate texture.
*/
void	b_draw_textured_walls(t_cubed *cubed, t_ray_calc *ray, 
t_draw_info *draw)
{
	unsigned int	color;
	double			y_step;
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
		ft_pixel_put(cubed->raycast_info->r_img, 
			draw->project_x, draw->project_y, color);
		draw->project_y++;
		draw->tex.y += y_step;
	}
}

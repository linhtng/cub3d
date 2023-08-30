/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:10:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 16:24:56 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * load_texture() gets a t_img_data with the new mlx img from the xpm filepaths
 * in the map file.
*/
void	load_texture(t_scene *scene, t_cubed *cubed)
{
	scene->texture[NORTH] = get_new_xpm_image(cubed, scene->elems.north);
	scene->texture[SOUTH] = get_new_xpm_image(cubed, scene->elems.south);
	scene->texture[EAST] = get_new_xpm_image(cubed, scene->elems.east);
	scene->texture[WEST] = get_new_xpm_image(cubed, scene->elems.west);
}

/*
 * get_texture_vec() calculates the texture vector for the raycasted vertical 
 * stripe of wall. The y is calulated by the difference, if any, between the 
 * line size and the projection height. The x is calculated by the direction 
 * of the ray and the position of the hit. 
*/
static t_vector	get_texture_vec(t_vector *hit, int dir, float y_step, \
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

/*
 * clip_line_height() clips the line height to the projection height if the
 * line height is greater than the projection height. Otherwise, it rounds the
 * line height to the nearest integer.
*/
static float	clip_line_height(float to_clip)
{
	float	line_height;

	if (to_clip > PROJECTION_HEIGHT)
		line_height = PROJECTION_HEIGHT;
	else
		line_height = round(to_clip);
	return (line_height);
}

/*
 * draw_textured_walls() draws the textured walls based on the direction of the
 * ray and the position of the hit. 
 * line_height = distance of the ray and the angle of the ray. 
 * y_step = the texture size and the line height and determines how quicly the
 * texture is traversed.
 * texture = the texture vector for the raycasted vertical stripe of wall.
 * pane_y_color = [0]the projected y corrdinate, [1]the color of the pixel to 
 * be drawn.
 * drawn_count = the number of pixels drawn.
*/
void	draw_textured_walls(t_cubed *cubed, int project_x, t_ray_calc *ray, \
int dir)
{
	float			line_height;
	unsigned int	pane_y_color[2];
	float			y_step;
	t_vector		texture;
	int				drawn_count;

	line_height = CELL_SIZE * PROJECTION_HEIGHT / ray->distance;
	y_step = TEXTURE_SIZE / line_height;
	if (ray->shortest == 'v')
		texture = get_texture_vec(&ray->v_map, dir, y_step, line_height);
	else
		texture = get_texture_vec(&ray->h_map, dir, y_step, line_height);
	line_height = clip_line_height(line_height);
	pane_y_color[0] = (PROJECTION_HEIGHT - line_height) / 2;
	drawn_count = 0;
	while (drawn_count++ < line_height)
	{
		pane_y_color[1] = ft_pixel_get(cubed->scene->texture[dir], \
		texture.x, texture.y);
		ft_pixel_put(cubed->raycast_info->r_img, project_x, \
		pane_y_color[0], pane_y_color[1]);
		pane_y_color[0]++;
		texture.y += y_step;
	}
}

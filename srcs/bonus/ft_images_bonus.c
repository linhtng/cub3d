/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:01:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/21 12:36:31 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_img_data	*get_new_image(t_cubed *cubed, int width, int height)
{
	t_img_data	*img;

	img = (t_img_data *) ft_calloc(1, sizeof(t_img_data));
	if (!img)
		mlx_close(cubed, 1, "cub3D: error: image allocation failed");
	img->img = mlx_new_image(cubed->mlx, width, height);
	if (!img->img)
	{
		free(img);
		mlx_close(cubed, 1, "cub3D: error: image allocation failed");
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	img->width = width;
	img->height = height;
	return (img);
}

t_img_data	*get_new_xpm_image(t_cubed *cubed, char *file_path)
{
	t_img_data	*img;

	img = (t_img_data *) ft_calloc(1, sizeof(t_img_data));
	if (!img)
		mlx_close(cubed, 1, "cub3D: error: image allocation failed");
	img->img = mlx_xpm_file_to_image(cubed->mlx, \
	file_path, &img->width, &img->height);
	if (!img->img)
	{
		free(img);
		mlx_close(cubed, 1, "cub3D: error: image allocation failed");
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	return (img);
}

void	refresh_images(t_cubed *cubed)
{
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	cubed->raycast_info->background_img->img, \
	WIN_WIDTH / 2 - PROJECTION_WIDTH / 2, RAYCAST_Y);
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	cubed->raycast_info->r_img->img, \
	WIN_WIDTH / 2 - PROJECTION_WIDTH / 2, RAYCAST_Y);
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	((t_cubed_bonus *)cubed)->minimap_img->img, MINIMAP_POS_X, MINIMAP_POS_Y);
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	((t_cubed_bonus *)cubed)->mini_player_img->img, \
	MINIMAP_POS_X, MINIMAP_POS_Y);
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	((t_cubed_bonus *)cubed)->frame_img->img, 0, 0);
	cubed->dirty_images = FALSE;
}

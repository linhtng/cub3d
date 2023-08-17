/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:01:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 17:00:41 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img_data	*get_new_image(t_cubed *cubed, int width, int height)
{
	t_img_data	*img;

	img = (t_img_data *) ft_calloc(1, sizeof(t_img_data));
	if (!img)
		return (NULL);//close
	img->img = mlx_new_image(cubed->mlx, width, height);
	if (!img->img)
	{
		free(img);
		return (NULL);//close
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
		return (NULL);//close
	img->img = mlx_xpm_file_to_image(cubed->mlx, file_path, &img->width, &img->height);
	if (!img->img)
	{
		free(img);
		return (NULL);//close
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	return (img);
}
//TODO add if bonus condition
void	refresh_images(t_cubed *cubed)
{
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	cubed->raycast_info->background_img->img, WIN_WIDTH / 2 - \
	PROJECTION_WIDTH / 2, WIN_HEIGHT / 2 - PROJECTION_HEIGHT / 2);
	mlx_put_image_to_window(cubed->mlx, cubed->window, \
	cubed->raycast_info->r_img->img, WIN_WIDTH / 2 - PROJECTION_WIDTH / 2, \
	WIN_HEIGHT / 2 - PROJECTION_HEIGHT / 2);
	cubed->dirty_images = FALSE;
}
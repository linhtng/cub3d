/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:24:40 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 14:23:34 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"

static void	ft_destroy_image(void *mlx, t_img_data **img)
{
	mlx_destroy_image(mlx, (*img)->img);
	free(*img);
	*img = NULL;
}
static void	destroy_all_images(t_cubed *cubed)
{
	if (cubed->raycast_info->r_img)
		ft_destroy_image(cubed->mlx, &(cubed->raycast_info->r_img));
	if (cubed->raycast_info->background_img)
		ft_destroy_image(cubed->mlx, &(cubed->raycast_info->background_img));
	if (cubed->scene->texture[NORTH])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[NORTH]));
	if (cubed->scene->texture[SOUTH])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[SOUTH]));
	if (cubed->scene->texture[EAST])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[EAST]));
	if (cubed->scene->texture[WEST])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[WEST]));
}

//TODO destroy and free all images and other allocated stuffs
int	mlx_close(t_cubed *cubed, int exit_code, char *exit_msg)
{
	printf("MLX should close...\n");
	destroy_all_images(cubed);
	if (cubed->window)
	{
		mlx_destroy_window(cubed->mlx, cubed->window);
		cubed->window = NULL;
	}
	if (cubed->mlx)
		cubed->mlx = NULL;
	if (exit_code)
		write(STDERR_FILENO, exit_msg , ft_strlen(exit_msg));//
	free_scene_data(cubed->scene);
	exit(exit_code);
	return (0);
}
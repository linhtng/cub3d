/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_close_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:24:40 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/26 18:39:16 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	ft_destroy_image(void *mlx, t_img_data **img)
{
	mlx_destroy_image(mlx, (*img)->img);
	free(*img);
	*img = NULL;
}

void	destroy_bonus_images(t_cubed_bonus *cubed, t_scene_bonus *scene)
{
	if (cubed->mini_player_img)
		ft_destroy_image(cubed->mlx, &(cubed->mini_player_img));
	if (cubed->minimap_img)
		ft_destroy_image(cubed->mlx, &(cubed->minimap_img));
	if (scene && scene->bonus_textures[0])
		ft_destroy_image(cubed->mlx, &scene->bonus_textures[0]);
	if (scene && scene->bonus_textures[1])
		ft_destroy_image(cubed->mlx, &scene->bonus_textures[1]);
	if (scene && scene->bonus_ceiling[0])
		ft_destroy_image(cubed->mlx, &scene->bonus_ceiling[0]);
	if (scene && scene->bonus_ceiling[1])
		ft_destroy_image(cubed->mlx, &scene->bonus_ceiling[1]);
	if (scene && scene->bonus_ceiling[2])
		ft_destroy_image(cubed->mlx, &scene->bonus_ceiling[2]);
}

static void	destroy_all_images(t_cubed_bonus *cubed)
{
	if (cubed->raycast_info && cubed->raycast_info->r_img)
		ft_destroy_image(cubed->mlx, &(cubed->raycast_info->r_img));
	if (cubed->raycast_info && cubed->raycast_info->background_img)
		ft_destroy_image(cubed->mlx, &(cubed->raycast_info->background_img));
	if (cubed->scene && cubed->scene->texture[NORTH])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[NORTH]));
	if (cubed->scene && cubed->scene->texture[SOUTH])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[SOUTH]));
	if (cubed->scene && cubed->scene->texture[EAST])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[EAST]));
	if (cubed->scene && cubed->scene->texture[WEST])
		ft_destroy_image(cubed->mlx, &(cubed->scene->texture[WEST]));
	destroy_bonus_images((t_cubed_bonus *)cubed, (t_scene_bonus *)cubed->scene);
}

int	mlx_close(t_cubed *cubed, int exit_code, char *exit_msg)
{
	printf("MLX should close...\n");
	destroy_all_images((t_cubed_bonus *)cubed);
	if (cubed->window)
	{
		mlx_destroy_window(cubed->mlx, cubed->window);
		cubed->window = NULL;
	}
	if (cubed->mlx)
		cubed->mlx = NULL;
	if (exit_code)
		ft_putendl_fd(exit_msg, STDERR_FILENO);
	if (cubed->scene)
		free_scene_data(cubed->scene);
	exit(exit_code);
	return (0);
}

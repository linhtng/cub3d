/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:24:40 by jebouche          #+#    #+#             */
/*   Updated: 2023/09/04 19:13:50 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * ft_destroy_image() frees the memory of a single mlx image, img->img the 
 * struct allocated for the image data, img.
*/
static void	ft_destroy_image(void *mlx, t_img_data **img)
{
	mlx_destroy_image(mlx, (*img)->img);
	free(*img);
	*img = NULL;
}

/*
 * destroy_all_images() frees all the allocated memory for the images 
 * for the program.
*/
static void	destroy_all_images(t_cubed *cubed)
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
}

/*
 * mlx_close() is called when the user presses the ESC key or closes the window
 * with the red X button or there is an allocation failure during setup. 
 * It frees all the allocated memory and exits the program, printing an error
 * message if necessary.
*/
int	mlx_close(t_cubed *cubed, int exit_code, char *exit_msg)
{
	destroy_all_images(cubed);
	if (cubed->window)
	{
		mlx_destroy_window(cubed->mlx, cubed->window);
		cubed->window = NULL;
	}
	if (cubed->mlx)
		cubed->mlx = NULL;
	if (exit_code)
		ft_putendl_fd(exit_msg, STDERR_FILENO);
	else
		ft_putstr_fd("Thanks for playin' cub3D!\n", STDOUT_FILENO);
	if (cubed->scene)
		free_scene_data(cubed->scene);
	system("export MallocStackLogging=1");
	system("leaks cub3D");
	exit(exit_code);
	return (0);
}

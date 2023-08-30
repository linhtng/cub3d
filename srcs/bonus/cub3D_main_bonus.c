/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:18:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 16:37:56 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * main() is the entry point of the program. If the parameter is not valid it 
 * will exit with EXIT_FAILURE. If the parameter is valid, it will initialize
 * the bonus scene and call raycast_start() to start the raycasting. If the map 
 * contents are not valid the program free the allocated date and end. Otherwise
 * it will call raycast_start() to start the raycasting.
 */
int	main(int argc, char **argv)
{
	int				fd;
	t_scene_bonus	b_scene;
	t_scene			*scene;

	scene = (t_scene *) &b_scene;
	if (argc == 2 && !DEBUG)
	{
		fd = open(argv[1], O_RDONLY);
		if (check_input_file(argv[1], fd, ".cub") == ERROR)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		init_scene(scene);
		if (get_scene_data(fd, scene) != ERROR)
			raycast_start(scene);
		free_scene_data(scene);
	}
	else if (DEBUG)
		mass_test_maps(argc - 1, &argv[1]);
	else
		ft_putendl_fd("Number of parameters must be 1.\n", STDERR_FILENO);
	return (0);
}

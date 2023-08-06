/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:18:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/06 21:03:47 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_input_file(char *argv, int fd, char *extension)
{
	if (fd == -1)
		return (err_msg(2, argv, "File cannot be opened."));
	if (ft_is_dir(argv))
		return (err_msg(2, argv, "Argument can't be a dir."));
	if (!correct_extension(argv, extension))
		return (err_msg(2, argv, "Invalid file extension"));
	return (1);
}

void	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(&scene->elems, 0, sizeof(t_elem));
	ft_memset(&scene->map, 0, sizeof(t_map));
	ft_memset(&scene->player, 0, sizeof(t_player));
	scene->elems.north = NULL;
	scene->elems.south = NULL;
	scene->elems.east = NULL;
	scene->elems.west = NULL;
	scene->array = NULL;
	scene->map.array = NULL;
	scene->map.flood = NULL;
	scene->map.visited = NULL;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (check_input_file(argv[1], fd, ".cub") == ERROR)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		init_scene(&scene);
		if (get_scene_data(fd, &scene) != ERROR)
			//print_scene(&scene);
			//print_arr(scene.array);
		free_arr(scene.array);
		free_arr(scene.map.array);
		free_arr(scene.map.flood);
		free_arr(scene.map.visited);
	}
	else
		printf("Number of parameters must be 1.\n");
	return (0);
}

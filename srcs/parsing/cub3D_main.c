/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:18:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/09 21:53:33 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "ft_raycast.h"

int	check_input_file(char *argv, int fd, char *extension)
{
	if (fd == -1)
		return (err_msg("File cannot be opened: ", argv));
	if (ft_is_dir(argv))
		return (err_msg("Expected file but found dir: ", argv));
	if (!correct_extension(argv, extension))
		return (err_msg(argv, " has invalid file extension"));
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
	scene->map.grid = NULL;
	scene->map.flood = NULL;
	scene->map.visited = NULL;
}

void	mass_test_maps(int argc, char **argv)
{
	int		fd[420];
	int		index;
	t_scene	scene[420];

	index = 0;
	while (index < argc)
	{
		printf("\033[0;33mResult of passing file %s: \033[0m\n", argv[index]);
		fd[index] = open(argv[index], O_RDONLY);
		if (check_input_file(argv[index], fd[index], ".cub") == ERROR)
		{
			close(fd[index]);
			index++;
			continue ;
		}
		init_scene(&scene[index]);
		if (get_scene_data(fd[index], &scene[index]) != ERROR)
			print_scene(&scene[index]);
		free_scene_data(&scene[index]);
		system("export MallocStackLogging=1");
		system("leaks cub3D");
		index++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;

	if (argc == 2 && !DEBUG)
	{
		fd = open(argv[1], O_RDONLY);
		if (check_input_file(argv[1], fd, ".cub") == ERROR)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		init_scene(&scene);
		if (get_scene_data(fd, &scene) != ERROR)
		{
			//print_scene(&scene);
			raycast_start(&scene);
		}
		free_scene_data(&scene);
	}
	else if (DEBUG)
		mass_test_maps(argc - 1, &argv[1]);
	else
		printf("Number of parameters must be 1.\n");
	return (0);
}

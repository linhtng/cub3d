/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:42:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/21 17:32:43 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_scene(t_scene *scene)
{
	int	i;

	i = 0;
	printf("map content:\n");
	print_arr(scene->map.grid);
	printf("NO: %s\n", scene->elems.north);
	printf("SO: %s\n", scene->elems.south);
	printf("WE: %s\n", scene->elems.west);
	printf("EA: %s\n", scene->elems.east);
	printf("floor color: %x\n", scene->elems.floor_color);
	printf("ceiling color: %x\n", scene->elems.ceiling_color);
	printf("player spawn dir is: %c, pos_y is: %d, pos_x is: %d\n", \
			scene->player.spawn, (int)scene->player.location.y, \
			(int)scene->player.location.x);
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

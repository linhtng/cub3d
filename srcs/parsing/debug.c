/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:42:04 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/14 16:50:13 by thuynguy         ###   ########.fr       */
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
		//free(arr[i]);
		i++;
	}
}

void	print_scene(t_scene *scene)
{
	int	i;

	i = 0;
	//print_arr(scene->array);
	printf("map content:\n");
	print_arr(scene->map.grid);
	printf("NO: %s\n", scene->elems.north);
	printf("SO: %s\n", scene->elems.south);
	printf("WE: %s\n", scene->elems.west);
	printf("EA: %s\n", scene->elems.east);
	printf("floor color: %x\n", scene->elems.floor_color);
	printf("ceiling color: %x\n", scene->elems.ceiling_color);
	printf("player spawn dir is: %c, pos_y is: %d, pos_x is: %d\n", 
			scene->player.spawn, (int)scene->player.location.y, (int)scene->player.location.x);
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

/* int	check_island(t_scene *scene, char **map)
{
	if (!(ft_arrdup(map, scene) == 1
			&& empty_map(scene) == 1))
		return (ERROR);
	//print_arr(scene->map.flood);
	//printf("map height: %d\n", scene->map.height);
	printf("map flood before flood start:\n");
	print_arr(scene->map.flood);
	 int	i = 0;
	while (i < scene->map.height)
		printf("len of each line in flood: %d\n", (int)ft_strlen(scene->map.flood[i++]));
	printf("map visited before flood start:\n");
	print_arr(scene->map.visited);
	//printf("player pos y: %d, pos x: %d\n", scene->player.pos_y, scene->player.pos_x);
	ft_flood(scene->player.pos_y, scene->player.pos_x, scene);
	printf("map flooded:\n");
	print_arr(scene->map.flood);
	printf("map visited after:\n");
	print_arr(scene->map.visited);
	printf("end\n");
	//print_arr(map);
	return (1);
} */
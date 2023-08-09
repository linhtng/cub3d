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
	print_arr(scene->map.array);
	printf("NO: %s\n", scene->elems.north);
	printf("SO: %s\n", scene->elems.south);
	printf("WE: %s\n", scene->elems.west);
	printf("EA: %s\n", scene->elems.east);
	printf("floor color: %lx\n", scene->elems.floor_color);
	printf("ceiling color: %lx\n", scene->elems.ceiling_color);
	printf("player spawn dir is: %c, pos_y is: %d, pos_x is: %d\n", 
			scene->player.spawn, scene->player.pos_y, scene->player.pos_x);
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
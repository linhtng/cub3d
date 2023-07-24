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
	print_arr(scene->array);
	printf("NO: %s\n", scene->elems.north);
	printf("SO: %s\n", scene->elems.south);
	printf("WE: %s\n", scene->elems.west);
	printf("EA: %s\n", scene->elems.east);
	printf("floor color: %d, %d, %d\n", scene->elems.floor_colors[0], scene->elems.floor_colors[1], scene->elems.floor_colors[2]);
	printf("ceiling color: %d, %d, %d\n", scene->elems.ceiling_colors[0], scene->elems.ceiling_colors[1], scene->elems.ceiling_colors[2]);
}
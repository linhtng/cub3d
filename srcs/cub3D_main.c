/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:18:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/18 16:18:10 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	main(int argc, char **argv)
{
	int				fd;
	t_scene	    	scene;

	if (argc == 2)
	{
		if (ft_is_dir(argv[1]))
			clean_exit("Argument can't be a dir.\n");
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			clean_exit("File cannot be opened.\n");
		correct_extension(argv[1], fd);
		ft_memset(&scene, 0, sizeof(t_scene));
		ft_memset(&scene.elems, 0, sizeof(t_elem));
		if (get_map(fd, &scene))
			print_scene(&scene);
	}
	else
		printf("Number of parameters must be 1.\n");
	free(scene.array);
	return (0);
}
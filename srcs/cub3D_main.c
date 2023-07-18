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
	char			**map;

	if (argc == 2)
	{
		if (ft_is_dir(argv[1]))
			clean_exit("Argument can't be a dir.\n");
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			clean_exit("File cannot be opened.\n");
		correct_extension(argv[1], fd);
		ft_bzero(&scene, sizeof(t_scene));
		map = get_valid_map(fd, &scene);
		if (map)
			game_init(map, scene);
	}
	else
		printf("Number of parameters must be 1.\n");
	return (0);
}
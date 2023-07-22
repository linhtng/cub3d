/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:18:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/22 21:01:17 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_input_file(char *argv, int fd)
{
    if (fd == -1)
        return (err_msg("File cannot be opened."));
	if (ft_is_dir(argv))
		return (err_msg("Argument can't be a dir."));
	if (!correct_extension(argv, ".cub"))
        return (err_msg("Map must have .cub extension."));
    return (1);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_scene	    	scene;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (check_input_file(argv[1], fd) == ERROR)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		ft_memset(&scene, 0, sizeof(t_scene));
		ft_memset(&scene.elems, 0, sizeof(t_elem));
		if (get_map(fd, &scene) == ERROR)
			print_scene(&scene);
	}
	else
		printf("Number of parameters must be 1.\n");
	free(scene.array);
	return (0);
}
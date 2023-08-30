/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:34 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 14:49:13 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	correct_extension(const char *argv, char *ending)
{
	size_t		len;
	const char	*extension;

	len = ft_strlen(argv);
	extension = ft_strnstr(argv, ending, len);
	if (!extension || ft_strncmp(extension, ending, ft_strlen(ending) + 1))
		return (0);
	return (1);
}

int	check_rgb_valid(t_scene *scene, char *line)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (scene->elems.fl_rgb[i] < 0 || scene->elems.fl_rgb[i] > 255
			|| scene->elems.c_rgb[i] < 0 || scene->elems.c_rgb[i] > 255)
			return (err_msg("Floor/ceiling color invalid: ", line));
		i++;
	}
	return (1);
}

unsigned int	convert_rgb_hex(int *rgb)
{
	unsigned int	res;

	res = ((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff);
	return (res);
}

void	free_scene_data(t_scene *scene)
{
	free_arr(scene->array);
	free_arr(scene->map.grid);
	free_arr(scene->map.flood);
	free_arr(scene->map.visited);
	if (scene->elems.north)
		free(scene->elems.north);
	if (scene->elems.south)
		free(scene->elems.south);
	if (scene->elems.east)
		free(scene->elems.east);
	if (scene->elems.west)
		free(scene->elems.west);
}

int	check_input_file(char *argv, int fd, char *extension)
{
	if (fd == -1)
		return (err_msg("File cannot be opened: ", argv));
	if (!correct_extension(argv, extension))
		return (err_msg(argv, " has invalid file extension"));
	return (1);
}

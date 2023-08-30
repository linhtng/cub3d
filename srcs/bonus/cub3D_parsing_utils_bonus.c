/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parsing_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:34 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 14:50:09 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (((t_scene_bonus *)scene)->bonus_elems.floor)
		free(((t_scene_bonus *)scene)->bonus_elems.floor);
	if (((t_scene_bonus *)scene)->bonus_elems.door)
		free(((t_scene_bonus *)scene)->bonus_elems.door);
	if (((t_scene_bonus *)scene)->bonus_elems.ceiling[0])
		free(((t_scene_bonus *)scene)->bonus_elems.ceiling[0]);
	if (((t_scene_bonus *)scene)->bonus_elems.ceiling[1])
		free(((t_scene_bonus *)scene)->bonus_elems.ceiling[1]);
	if (((t_scene_bonus *)scene)->bonus_elems.ceiling[2])
		free(((t_scene_bonus *)scene)->bonus_elems.ceiling[2]);
}

int	check_input_file(char *argv, int fd, char *extension)
{
	if (fd == -1)
		return (err_msg("File cannot be opened: ", argv));
	if (!correct_extension(argv, extension))
		return (err_msg(argv, " has invalid file extension"));
	return (1);
}

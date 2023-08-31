/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parsing_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:34 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/31 10:25:10 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * correct_extension() checks if the given file has the correct extension.
 * If it does, it returns 1. Otherwise, it returns 0.
 */
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

/*
 * free_scene_data() frees the all the data saved in the bounus scene 
 * struct.
 */
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

/*
 * check_input_file() checks if the given file can be opened and if it has
 * the correct extension. If it does, it returns 1. Otherwise, it returns -1
 * and print an explicit error message.
 */
int	check_input_file(char *argv, int fd, char *extension)
{
	if (fd == -1)
		return (err_msg("File cannot be opened: ", argv));
	if (!correct_extension(argv, extension))
		return (err_msg(argv, " has invalid file extension"));
	return (1);
}

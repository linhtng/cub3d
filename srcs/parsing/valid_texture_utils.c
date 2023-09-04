/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:00:37 by thuynguy          #+#    #+#             */
/*   Updated: 2023/09/04 19:07:18 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * check_valid_texture() checks if the given texture path is a valid xpm file,
 * and if it is duplicated. If valid, saved the path in the struct and 
 * returns 1. Otherwise, it returns -1 and print an explicit error message.
*/
static int	check_valid_texture(char **path, char *texture)
{
	int	fd;
	int	ret;

	if (!texture || !texture[0])
		return (err_msg("Empty texture info", NULL));
	if (*path)
		return (err_msg("Duplicate texture detected", NULL));
	*path = ft_strdup(texture);
	if (!*path)
		return (err_msg("Malloc error when getting texture", NULL));
	fd = open(*path, O_RDWR);
	ret = check_input_file(*path, fd, ".xpm");
	close(fd);
	return (ret);
}

/*
 * get_texture() checks if the given texture path is found and if it is valid.
 * If valid, returns 1. Otherwise, it returns -1.
*/
static int	get_texture(t_scene *scene, char *elem_id, char *texture, int len)
{
	int	ret;

	ret = -1;
	if (!ft_strncmp(elem_id, "NO", len))
		ret = check_valid_texture(&scene->elems.north, texture);
	else if (!ft_strncmp(elem_id, "SO", len))
		ret = check_valid_texture(&scene->elems.south, texture);
	else if (!ft_strncmp(elem_id, "WE", len))
		ret = check_valid_texture(&scene->elems.west, texture);
	else if (!ft_strncmp(elem_id, "EA", len))
		ret = check_valid_texture(&scene->elems.east, texture);
	else
		ret = err_msg("Invalid element info: ", elem_id);
	return (ret);
}

int	valid_texture_form(t_scene *scene, char *scene_line, char **single_elem)
{
	int		info_num;

	info_num = arr_len(single_elem);
	if (info_num == 1)
		scene->err_flag = get_texture(scene, single_elem[0], 
				&(single_elem[0])[2], 2);
	else if (info_num == 2)
		scene->err_flag = get_texture(scene, single_elem[0], single_elem[1], 3);
	else
		return (err_msg("Unexpected number of element info: ", scene_line));
	return (scene->err_flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_elems_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:10:18 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/31 21:20:47 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
static int	get_bonus_texture(t_scene_bonus *scene, char *elem_id, \
char *texture, int len)
{
	int			ret;
	int			i;

	ret = -1;
	i = 0;
	if (!ft_strncmp(elem_id, "DO", len))
		ret = check_valid_texture(&scene->bonus_elems.door, texture);
	else if (!ft_strncmp(elem_id, "F", len))
		ret = check_valid_texture(&scene->bonus_elems.floor, texture);
	else if (!ft_strncmp(elem_id, "C", len))
	{
		while (scene->bonus_elems.ceiling[i])
			i++;
		ret = check_valid_texture(&(scene->bonus_elems.ceiling[i]), texture);
	}
	else
		ret = err_msg("Invalid element info: ", elem_id);
	return (ret);
}

/*
 * get_texture() checks if the given texture path is found and if it is valid.
 * If valid, returns 1. Otherwise, it returns -1.
*/
static int	get_texture(t_scene_bonus *scene, char *elem_id, \
char *texture, int len)
{
	int			ret;

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
		ret = get_bonus_texture(scene, elem_id, texture, len);
	return (ret);
}

/*
 * get_scene_elem() takes the string of scene element info, split it into 
 * a string of array with the ' ' as delimiter. This array is then passed
 * to get_texture() or get_scene_color() to get the elements.
*/
int	get_scene_elem(t_scene *scene, char *scene_line)
{
	int		info_num;
	char	**single_elem;

	if (ft_isemptystr(scene_line))
		return (0);
	single_elem = ft_split(scene_line, ' ');
	if (!single_elem)
		return (err_msg("Malloc error when getting scene's elem info", NULL));
	if (!ft_strchr("NOSWEAFCD", single_elem[0][0]))
	{
		scene->err_flag = ERROR;
		free_arr(single_elem);
		return (err_msg("Invalid/Missing element info: ", scene_line));
	}
	info_num = arr_len(single_elem);
	if (ft_strchr("NOSWEADFC", single_elem[0][0]) && info_num == 1)
		scene->err_flag = get_texture((t_scene_bonus *)scene, single_elem[0], \
		&(single_elem[0])[2], 2);
	else if (ft_strchr("NOSWEADFC", single_elem[0][0]) && info_num == 2)
		scene->err_flag = get_texture((t_scene_bonus *)scene, \
		single_elem[0], single_elem[1], 3);
	free_arr(single_elem);
	return (scene->err_flag);
}

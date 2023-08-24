/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_elems_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:10:18 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/24 19:48:28 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

static int	get_texture(t_scene_bonus *scene, char *elem_id, \
char *texture, int len)
{
	int			ret;
	static int	i;

	ret = -1;
	i = 0;
	if (!ft_strncmp(elem_id, "NO", len))
		ret = check_valid_texture(&scene->elems.north, texture);
	if (!ft_strncmp(elem_id, "SO", len))
		ret = check_valid_texture(&scene->elems.south, texture);
	if (!ft_strncmp(elem_id, "WE", len))
		ret = check_valid_texture(&scene->elems.west, texture);
	if (!ft_strncmp(elem_id, "EA", len))
		ret = check_valid_texture(&scene->elems.east, texture);
	if (!ft_strncmp(elem_id, "DO", len))
		ret = check_valid_texture(&scene->bonus_elems.door, texture);
	if (!ft_strncmp(elem_id, "F", len))
		ret = check_valid_texture(&scene->bonus_elems.floor, texture);
	if (!ft_strncmp(elem_id, "C", len))
	{
		while (scene->bonus_elems.ceiling[i])
			i++;
		ret = check_valid_texture(&(scene->bonus_elems.ceiling[i]), texture);
	}
	return (ret);
}

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

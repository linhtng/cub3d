/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_elems.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:10:18 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/09 17:56:08 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_valid_texture(char **path, char *texture)
{
	int	fd;
	int	ret;

	if (!texture || !texture[0])
		return (err_msg(1, "Empty texture info"));
	if (*path)
		return (err_msg(1, "Duplicate texture detected"));
	*path = ft_strdup(texture);
	if (!*path)
		return (err_msg(1, "Malloc error when getting texture path"));
	fd = open(*path, O_RDONLY);
	ret = check_input_file(*path, fd, ".xpm");
	close(fd);
	return (ret);
}

static int	get_texture(t_scene *scene, char *elem_id, char *texture, int len)
{
	int	ret;

	ret = -1;
	if (!ft_strncmp(elem_id, "NO", len))
		ret = check_valid_texture(&scene->elems.north, texture);
	if (!ft_strncmp(elem_id, "SO", len))
		ret = check_valid_texture(&scene->elems.south, texture);
	if (!ft_strncmp(elem_id, "WE", len))
		ret = check_valid_texture(&scene->elems.west, texture);
	if (!ft_strncmp(elem_id, "EA", len))
		ret = check_valid_texture(&scene->elems.east, texture);
	return (ret);
}

static int	get_rgb_color(t_scene *scene, char **color, int id, char *line)
{
	if (id == FLOOR)
	{
		if (scene->elems.fl_rgb[3])
			return (err_msg(1, "Duplicate floor texture detected"));
		scene->elems.fl_rgb[0] = ft_atoi(&(color[0])[1]);
		scene->elems.fl_rgb[1] = ft_atoi(color[1]);
		scene->elems.fl_rgb[2] = ft_atoi(color[2]);
		scene->elems.fl_rgb[3]++;
	}
	if (id == CEILING)
	{
		if (scene->elems.c_rgb[3])
			return (err_msg(1, "Duplicate ceiling texture detected"));
		scene->elems.c_rgb[0] = ft_atoi(&(color[0])[1]);
		scene->elems.c_rgb[1] = ft_atoi(color[1]);
		scene->elems.c_rgb[2] = ft_atoi(color[2]);
		scene->elems.c_rgb[3]++;
	}
	return (check_rgb_valid(scene, line));
}

static int	get_scene_color(t_scene *scene, char *scene_line)
{
	int		ret;
	int		i;
	char	**color_arr;

	ret = -1;
	i = 0;
	if (count_occurences(scene_line, ',') != 2)
		return (err_msg(2, "Invalid color info.", scene_line));
	while (ft_isspace(*scene_line))
		scene_line++;
	color_arr = ft_split(scene_line, ',');
	if (!color_arr || arr_len(color_arr) != 3)
		return (err_msg(2, "Invalid color info.", scene_line));
	if (color_arr[0][0] == 'F')
		ret = get_rgb_color(scene, color_arr, FLOOR, scene_line);
	else if (color_arr[0][0] == 'C')
		ret = get_rgb_color(scene, color_arr, CEILING, scene_line);
	if (ret != ERROR)
	{
		scene->elems.ceiling_color = convert_rgb_hex(scene->elems.c_rgb);
		scene->elems.floor_color = convert_rgb_hex(scene->elems.fl_rgb);
	}
	free_arr(color_arr);
	return (ret);
}

int	get_scene_elem(t_scene *scene, char *scene_line)
{
	int		info_num;
	char	**single_elem;
	int		ret;

	if (ft_isemptystr(scene_line))
		return (0);
	single_elem = ft_split(scene_line, ' ');
	if (!single_elem || !ft_strchr("NOSWEAFC", single_elem[0][0]))
	{
		scene->err_flag = 1;
		return (err_msg(1, "Invalid/Missing element info."));
	}
	ret = 0;
	info_num = arr_len(single_elem);
	if (ft_strchr("NOSWEA", single_elem[0][0]) && info_num == 1)
		ret = get_texture(scene, single_elem[0], &(single_elem[0])[2], 2);
	else if (ft_strchr("NOSWEA", single_elem[0][0]) && info_num == 2)
		ret = get_texture(scene, single_elem[0], single_elem[1], 3);
	else if (ft_strchr("FC", single_elem[0][0]))
		ret = get_scene_color(scene, scene_line);
	free_arr(single_elem);
	if (ret == ERROR)
		scene->err_flag = 1;
	return (ret);
}

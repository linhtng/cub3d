/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_elems.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:10:18 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/24 20:24:39 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_valid_texture(char *texture)
{
	int	fd;
	int	ret;

	if (!texture)
		return (ERROR);
	fd = open(texture, O_RDONLY);
	ret = check_input_file(texture, fd, ".xpm");
	close(fd);
	return (ret);
}

static int	get_texture(t_scene *scene, char *elem_id, char *texture, int len)
{
	int	ret;

	ret = -1;
	if (!ft_strncmp(elem_id, "NO", len) && !scene->elems.north)
	{
		scene->elems.north = ft_strdup(texture);
		ret = check_valid_texture(scene->elems.north);
	}
	if (!ft_strncmp(elem_id, "SO", len) && !scene->elems.south)
	{
		scene->elems.south = ft_strdup(texture);
		ret = check_valid_texture(scene->elems.south);
	}
	if (!ft_strncmp(elem_id, "WE", len) && !scene->elems.west)
	{
		scene->elems.west = ft_strdup(texture);
		ret = check_valid_texture(scene->elems.west);
	}
	if (!ft_strncmp(elem_id, "EA", len) && !scene->elems.east)
	{
		scene->elems.east = ft_strdup(texture);
		ret = check_valid_texture(scene->elems.east);
	}
	return (ret);
}

static int	get_rgb_color(t_scene *scene, char **color_arr, int id, char *scene_line)
{
	int	i;

	i = 0;
	if (id == FLOOR)
	{
		scene->elems.floor_colors[0] = ft_atoi(&(color_arr[0])[1]);
		scene->elems.floor_colors[1] = ft_atoi(color_arr[1]);
		scene->elems.floor_colors[2] = ft_atoi(color_arr[2]);
		scene->elems.floor_colors[3]++;
	}
	if (id == CEILING)
	{
		scene->elems.ceiling_colors[0] = ft_atoi(&(color_arr[0])[1]);
		scene->elems.ceiling_colors[1] = ft_atoi(color_arr[1]);
		scene->elems.ceiling_colors[2] = ft_atoi(color_arr[2]);
		scene->elems.ceiling_colors[3]++;
	}
	while (i < 3)
	{
		if (scene->elems.floor_colors[i] < 0 || scene->elems.floor_colors[i] > 255
			|| scene->elems.ceiling_colors[i] < 0 || scene->elems.ceiling_colors[i] > 255)
			return (err_msg(2, scene_line, "Floor/ceiling color invalid."));
		i++;
	}
	return (1);
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
	if (color_arr[0][0] == 'F' && !scene->elems.floor_colors[3])
		ret = get_rgb_color(scene, color_arr, FLOOR, scene_line);
	else if (color_arr[0][0] == 'C' && !scene->elems.ceiling_colors[3])
		ret = get_rgb_color(scene, color_arr, CEILING, scene_line);
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
		//printf("%s\n", single_elem[0]);
		return (0);
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
	if (ret == -1)
		scene->err_flag = 1;
	return (ret);
}

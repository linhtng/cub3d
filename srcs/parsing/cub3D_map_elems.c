/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_elems.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:10:18 by thuynguy          #+#    #+#             */
/*   Updated: 2023/09/04 19:05:27 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * get_rgb_color() use ft_atoi to convert the given string to integer, 
 * which represents the color. If the color is not duplicated, 
 * it is saved in the struct. Passed the color to check_rgb_valid() to check.
*/
static int	get_rgb_color(t_scene *scene, char **color, int id, char *line)
{
	if (id == FLOOR)
	{
		if (scene->elems.fl_rgb[3])
			return (err_msg("Duplicate floor color detected", NULL));
		scene->elems.fl_rgb[0] = ft_atoi(&(color[0])[1]);
		scene->elems.fl_rgb[1] = ft_atoi(color[1]);
		scene->elems.fl_rgb[2] = ft_atoi(color[2]);
		scene->elems.fl_rgb[3]++;
	}
	if (id == CEILING)
	{
		if (scene->elems.c_rgb[3])
			return (err_msg("Duplicate ceiling color detected", NULL));
		scene->elems.c_rgb[0] = ft_atoi(&(color[0])[1]);
		scene->elems.c_rgb[1] = ft_atoi(color[1]);
		scene->elems.c_rgb[2] = ft_atoi(color[2]);
		scene->elems.c_rgb[3]++;
	}
	return (check_rgb_valid(scene, line));
}

/*
 * get_scene_color() takes the string of color info, split it into 
 * a string of array with the ',' as delimiter. This array is then passed
 * to get_rgb_color() to get the colors as integers. If the 
 * integer colors are valid, they will be converted to hexadecimal.
*/
static int	get_scene_color(t_scene *scene, char *scene_line)
{
	char	**color_arr;

	scene->err_flag = ERROR;
	if (count_occurences(scene_line, ',') != 2)
		return (err_msg("Invalid color info: ", scene_line));
	while (ft_isspace(*scene_line))
		scene_line++;
	color_arr = ft_split(scene_line, ',');
	if (!color_arr || arr_len(color_arr) != 3)
	{
		free_arr(color_arr);
		return (err_msg("Invalid color info: ", scene_line));
	}
	if (color_arr[0][0] == 'F')
		scene->err_flag = get_rgb_color(scene, color_arr, FLOOR, scene_line);
	else if (color_arr[0][0] == 'C')
		scene->err_flag = get_rgb_color(scene, color_arr, CEILING, scene_line);
	if (scene->err_flag != ERROR)
	{
		scene->elems.ceiling_color = convert_rgb_hex(scene->elems.c_rgb);
		scene->elems.floor_color = convert_rgb_hex(scene->elems.fl_rgb);
	}
	free_arr(color_arr);
	return (scene->err_flag);
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
	if (!ft_strchr("NOSWEAFC", single_elem[0][0]))
	{
		scene->err_flag = ERROR;
		free_arr(single_elem);
		return (err_msg("Invalid/Missing element info: ", scene_line));
	}
	info_num = arr_len(single_elem);
	if (ft_strchr("NOSWEA", single_elem[0][0]))
		scene->err_flag = valid_texture_form(scene, scene_line, single_elem);
	else if (ft_strchr("FC", single_elem[0][0]))
		scene->err_flag = get_scene_color(scene, scene_line);
	free_arr(single_elem);
	return (scene->err_flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:15:59 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/18 21:16:05 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

static char	*get_scene_string(int fd)
{
	char	*buf;
	char	*raw_str;
	char	*trimmed_str;

	raw_str = NULL;
	trimmed_str = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		raw_str = ft_strjoin(raw_str, buf);
		if (!raw_str)
		{
			free(buf);
			return (NULL);
		}
		free(buf);
		buf = get_next_line(fd);
	}
	if (raw_str)
	{
		trimmed_str = ft_strtrim(raw_str, " \t\v\f\r\n");
		free(raw_str);
	}
	return (trimmed_str);
}

int	parse_scene_texture(t_scene *scene, char **elem)
{
	char	*elem_id;

	elem_id = elem[0];
	if (!ft_strncmp(elem_id, "NO", 2))
		scene->elems.north = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem_id, "SO", 2))
		scene->elems.south = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem_id, "WE", 2))
		scene->elems.west = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem_id, "EA", 2))
		scene->elems.west = ft_strdup(elem[1]);
	else
		return (0);
	return (1);
}

int	parse_scene_color(t_scene *scene, char **elem)
{
	if (!ft_strncmp(elem[0], "F", 1) || !ft_strncmp(elem[0], "C", 1))
		//get_color_elem(scene, str);

	return (1);
}

int	get_scene_elem(t_scene *scene, char *str)
{
	int		info_num;
	char	**single_elem;
	int		ret;

	single_elem = NULL;
	single_elem = ft_split(str, ' ');
	if (!single_elem)
		return (-1);
	ret = 0;
	info_num = arr_len(single_elem);
	if (info_num == 2)
		ret = parse_scene_texture(scene, single_elem);
	else if (info_num >= 2 && info_num <= 4)
		ret = parse_scene_color(scene, single_elem);
	free_arr(single_elem);
	return (ret);
}

int	valid_elem(char **scene_arr, t_scene *scene)
{
	int	i;

	i = 0;
	if (!ft_strchr("NOSWEAFC", scene_arr[0][0]))
		return (0);
	while (scene_arr[i]) //break when scene->elem->elem_num == 6
	{
		get_scene_elem(scene, scene_arr[i]);
		i++;
	}
	return (1);
}

int	valid_map(int fd, t_scene *scene)
{
	char	*scene_str;
	char	**scene_arr;
	int		arr_len;	

	scene_str = get_scene_string(fd);
	if (!scene_str)
	{
		printf("Error\nFailed to get the scene string.\n");
		return (0);
	}
	arr_len = ft_strlen(scene_str) - count_occurences(scene_str, '\n');
	scene_arr = ft_split(scene_str, '\n');
	if (!scene_arr)
	{
		free(scene_str);
		return (0);
	}
	free(scene_str);
	scene->array = scene_arr;
	/* if (!valid_elem(scene_arr, scene) || !valid_map_content(scene_arr, scene))
	{
		free_arr(scene_arr);
		printf("Error\nInvalid map\n");
		return (0);
	} */
	return (1);
}


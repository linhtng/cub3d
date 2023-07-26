/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:15:59 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/26 20:48:02 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*get_scene_string(t_scene *scene, int fd)
{
	char	*buf;
	char	*raw_str;
	char	*trimmed_str;

	raw_str = NULL;
	trimmed_str = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		scene->len++;
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

static int	get_scene_arr(t_scene *scene, char *scene_str, int len)
{
	char	*endl;
	char	*begin;
	char	**arr;

	endl = ft_strchr(scene_str, '\n');
	begin = scene_str;
	arr = scene->array;
	while (endl)
	{
		*arr = ft_substr(scene_str, (size_t) (begin - scene_str), (size_t)(endl++ - begin));
		if (!*arr)
			return (err_msg(1, "Malloc err when getting the scene_arr."));
		scene->len++;
		arr++;
		begin = endl;
		endl = ft_strchr(begin, '\n');
	}
	if (begin)
	{
		*arr = ft_substr(scene_str, (size_t) (begin - scene_str), (size_t)(&scene_str[len] - begin));
		if (!*arr)
			return (err_msg(1, "Malloc err when getting the scene_arr."));
		scene->len++;
	}
	return (1);
}

static int	get_map_elems(char **scene_arr, t_scene *scene)
{
	int		i;

	i = 0;
	if (!ft_strchr("NOSWEAFC", scene_arr[0][0]))
		return (err_msg(2, "Invalid element info.", scene_arr[i]));
	while (scene_arr[i])
	{
		scene->elems.filled_elem += get_scene_elem(scene, scene_arr[i]);
		if (scene->elems.filled_elem == 6 || scene->err_flag)
		{
			if (scene->err_flag)
				return (err_msg(2, "line where err encountered:", scene_arr[i])); //debug, del later
			break ;
		}
		i++;
	}
	if (scene->elems.filled_elem != 6)
		return (err_msg(1, "Missing element(s) from the scene file."));
	while (ft_isemptystr(scene_arr[i + 1]))
		i++;
	return (get_map_content(&scene_arr[i + 1], scene, i + 1));
}

int	get_scene_data(int fd, t_scene *scene)
{
	char	*scene_str;
	char	**scene_arr;
	int		ret;

	ret = -1;
	scene_str = get_scene_string(scene, fd);
	close(fd);
	if (!scene_str)
		return (err_msg(1, "Emty map/Malloc err when getting the scene str."));
	scene_arr = (char **) ft_calloc(scene->len + 1, sizeof(char *));
	if (scene_arr)
	{
		scene->array = scene_arr;
		scene->len = 0;
		ret = get_scene_arr(scene, scene_str, ft_strlen(scene_str));
		free(scene_str);
		if (ret == 1)
		{
			if (get_map_elems(scene->array, scene) == ERROR || scene->err_flag)
				return (ERROR);
		}
	/* if (!valid_elem(scene_arr, scene) || !valid_map_content(scene_arr, scene))
	{
		free_arr(scene_arr);
		printf("Error\nInvalid map\n");
		return (0);
	} */
	}
	return (ret);
}

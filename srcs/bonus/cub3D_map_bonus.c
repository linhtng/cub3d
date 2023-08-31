/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:15:59 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/31 10:29:51 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
 * get_scene_string reads the file descriptor fd and returns a string
 * containing the whole file. The string is trimmed of all leading and
 * trailing whitespaces.
*/
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

/*
 * get_scene_arr() splits the scene string str into an array of strings
 * using the newline character as a delimiter. The array is stored in
 * scene->array and all empty lines (if any) are preserved.
*/
static int	get_scene_arr(t_scene *scene, char *str, int len)
{
	char	*endl;
	char	*begin;
	char	**arr;

	endl = ft_strchr(str, '\n');
	begin = str;
	arr = scene->array;
	while (endl)
	{
		*arr = ft_substr(str, (int)(begin - str), (int)(endl++ - begin));
		if (!*arr)
			return (err_msg("Malloc err when getting the scene_arr.", NULL));
		scene->len++;
		arr++;
		begin = endl;
		endl = ft_strchr(begin, '\n');
	}
	if (begin)
	{
		*arr = ft_substr(str, (int)(begin - str), (int)(&str[len] - begin));
		if (!*arr)
			return (err_msg("Malloc err when getting the scene_arr.", NULL));
		scene->len++;
	}
	return (1);
}

/*
 * get_map_elems() go through the scene_arr and save the elements
 * into the scene struct. The function returns 1 if all the elements
 * are found and no error happened. After the elements are saved,
 * the function calls get_map_content() to save the map content.
*/
static int	get_map_elems(char **scene_arr, t_scene *scene)
{
	int		i;

	i = 0;
	if (!ft_strchr("NOSWEAFCD", scene_arr[0][0]))
		return (err_msg("Invalid element info: ", scene_arr[i]));
	while (scene_arr[i])
	{
		scene->elems.filled_elem += get_scene_elem(scene, scene_arr[i++]);
		if (scene->elems.filled_elem == NUM_ELEMS || scene->err_flag == ERROR)
			break ;
	}
	if (scene->elems.filled_elem != NUM_ELEMS)
		return (ERROR);
	while (scene_arr[i] && ft_isemptystr(scene_arr[i]))
		i++;
	scene->map.height = scene->len - i;
	if (scene->map.height < 3)
		return (err_msg("Map content less than 3 lines.", NULL));
	return (get_map_content(&scene_arr[i], scene, i));
}

/*
 * get_scene_data() got the scene string from the given file, 
 * then transfer it into a 2D array of strings. The function returns 1 
 * if all the elements is found and no error happened. 
 * Otherwise, it returns -1.
*/
int	get_scene_data(int fd, t_scene *scene)
{
	char	*scene_str;
	char	**scene_arr;
	int		ret;

	ret = -1;
	scene_str = get_scene_string(scene, fd);
	close(fd);
	if (!scene_str)
		return (err_msg("Emty map/Malloc err at scene str.", NULL));
	scene_arr = (char **) ft_calloc(scene->len + 1, sizeof(char *));
	if (scene_arr)
	{
		scene->array = scene_arr;
		scene->len = 0;
		ret = get_scene_arr(scene, scene_str, ft_strlen(scene_str));
		free(scene_str);
		if (ret == 1)
		{
			if (get_map_elems(scene->array, scene) == ERROR
				|| scene->err_flag == ERROR)
				return (ERROR);
		}
	}
	return (ret);
}

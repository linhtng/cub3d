/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:15:59 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/22 21:10:58 by thuynguy         ###   ########.fr       */
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

int	get_texture(t_scene *scene, char *elem_id, char *texture, int len)
{
	int	ret;

	ret = -1;
	if (!ft_strncmp(elem_id, "NO", len) && !scene->elems.north)
	{
		scene->elems.north = ft_strdup(texture);
		ret = 1;
	}
	if (!ft_strncmp(elem_id, "SO", len) && !scene->elems.south)
	{
		scene->elems.south = ft_strdup(texture);
		ret = 1;
	}
	if (!ft_strncmp(elem_id, "WE", len) && !scene->elems.west)
	{
		scene->elems.west = ft_strdup(texture);
		ret = 1;
	}
	if (!ft_strncmp(elem_id, "EA", len) && !scene->elems.east)
	{
		scene->elems.east = ft_strdup(texture);
		ret = 1;
	}
	return (ret);
}

static int	get_rgb_color(t_scene *scene, char **color_arr, int id)
{
	int	i;

	i = 0;
	if (id == FLOOR)
	{
		scene->elems.floor_colors[0] = ft_atoi(&(color_arr[0])[1]);
		scene->elems.floor_colors[1] = ft_atoi(color_arr[1]);
		scene->elems.floor_colors[2] = ft_atoi(color_arr[2]);
	}
	if (id == CEILING)
	{
		scene->elems.ceiling_colors[0] = ft_atoi(&(color_arr[0])[1]);
		scene->elems.ceiling_colors[1] = ft_atoi(color_arr[1]);
		scene->elems.ceiling_colors[2] = ft_atoi(color_arr[2]);
	}
	while (i < 3)
	{
		if (scene->elems.floor_colors[i] < 0 || scene->elems.floor_colors[i] > 255
			|| scene->elems.ceiling_colors[i] < 0 || scene->elems.ceiling_colors[i] > 255)
			return (err_msg("Floor/ceiling color invalid."));
		i++;
	}
	return (1);
}

int	get_scene_color(t_scene *scene, char *scene_line)
{
	int		ret;
	int		i;
	char	**color_arr;

	ret = -1;
	i = 0;
	if (count_occurences(scene_line, ',') != 2)
		return (err_msg("Invalid color info."));
	while (ft_isspace(*scene_line))
		scene_line++;
	color_arr = ft_split(scene_line, ',');
	if (!color_arr || arr_len(color_arr) != 3)
		return (err_msg("Invalid color info."));
	if (color_arr[0][0] == 'F')
		ret = get_rgb_color(scene, color_arr, FLOOR);
	else if (color_arr[0][0] == 'C')
		ret = get_rgb_color(scene, color_arr, CEILING);
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

int	get_map_elem(char **scene_arr, t_scene *scene)
{
	int		i;

	i = 0;
	if (!ft_strchr("NOSWEAFC", scene_arr[0][0]))
		return (0);
	while (scene_arr[i])
	{
		scene->elems.filled_elem += get_scene_elem(scene, scene_arr[i]);
		if (scene->elems.filled_elem == 6 || scene->err_flag)
		{
			if (scene->err_flag)
				printf("line where err encountered: %s\n", scene_arr[i]); //debug, del later
			break ;
		}
		i++;
	}
	return (1);
}

int	get_map(int fd, t_scene *scene)
{
	char	*scene_str;
	char	**scene_arr;
	//int		arr_len;	

	scene_str = get_scene_string(fd);
	close(fd);
	if (!scene_str)
		return(err_msg("Failed to get the scene string.\n"));
	scene_arr = ft_split(scene_str, '\n');
	if (!scene_arr)
	{
		free(scene_str);
		return (err_msg("Failed to get the scene array.\n"));
	}
	free(scene_str);
	scene->array = scene_arr;
	if (!get_map_elem(scene_arr, scene) || scene->err_flag)
	{
		printf("Misconfigured scene element detected\n");
		return (0);
	}
	/* if (!valid_elem(scene_arr, scene) || !valid_map_content(scene_arr, scene))
	{
		free_arr(scene_arr);
		printf("Error\nInvalid map\n");
		return (0);
	} */
	return (1);
}


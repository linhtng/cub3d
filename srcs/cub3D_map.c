/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:15:59 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/24 20:35:55 by thuynguy         ###   ########.fr       */
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

/* int	get_map_content(char **scene_arr, t_scene *scene, int i)
{
	while (ft_isemptystr(scene_arr[i]))
		i++;
	while (scene_arr[i])
	{
		if (!ft_isdigit)
	}
} */

int	get_map_elems(char **scene_arr, t_scene *scene)
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
			//return (ERROR);
			//return (err_msg(1, "Scene element(s) invalid and/or missing."));
		}
		i++;
	}
	if (scene->elems.filled_elem != 6)
		return (err_msg(1, "Missing element(s) from the scene file."));
	//printf("%s\n", scene_arr[i]);
	scene->map.array = &scene_arr[i + 1];
	printf("Scene map arr:\n");
	print_arr(scene->map.array);
	//get_map_content();
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
		return(err_msg(1, "Emty map/Malloc err when getting the scene string."));
	scene_arr = ft_split(scene_str, '\n');
	if (!scene_arr)
	{
		free(scene_str);
		return (err_msg(1, "Failed to get the scene array."));
	}
	free(scene_str);
	scene->array = scene_arr;
	if (get_map_elems(scene_arr, scene) == ERROR || scene->err_flag)
		return (ERROR);
	/* if (!valid_elem(scene_arr, scene) || !valid_map_content(scene_arr, scene))
	{
		free_arr(scene_arr);
		printf("Error\nInvalid map\n");
		return (0);
	} */
	return (1);
}


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

static char	*get_map_string(int fd, t_scene *scene)
{
	char	*buf;
	char	*map_string;

	map_string = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		map_string = ft_strjoin(map_string, buf);
		if (!map_string)
		{
			free(buf);
			close(fd);
			clean_exit("Map string allocation failed.\n");
		}
		scene->lines++;
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
	return (map_string);
}

int	check_map_content(int fd, t_scene *mapdata)
{
	char	*map_str;
	char	**map_arr;
	int		arr_len;	

	map_str = get_map_string(fd, mapdata);
	if (!map_str)
		return (0);
	arr_len = ft_strlen(map_str) - count_occurences(map_str, '\n');
	map_arr = ft_split(map_str, '\n');
	if (!map_arr)
	{
		free(map_str);
		return (0);
	}
	free(map_str);
	if (!valid_elem(map_arr, mapdata) || !valid_map_content(map_arr, mapdata))
	{
		free_arr(map_arr);
		return (0);
	}
	return (1);
}


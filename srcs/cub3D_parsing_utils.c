/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:34 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/09 18:10:32 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	correct_extension(const char *argv, char *ending)
{
	size_t		len;
	const char	*extension;

	len = ft_strlen(argv);
	extension = ft_strnstr(argv, ending, len);
	if (!extension || ft_strncmp(extension, ending, ft_strlen(ending) + 1))
		return (0);
	return (1);
}

int	check_rgb_valid(t_scene *scene, char *line)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (scene->elems.fl_rgb[i] < 0 || scene->elems.fl_rgb[i] > 255
			|| scene->elems.c_rgb[i] < 0 || scene->elems.c_rgb[i] > 255)
			return (err_msg(2, "Floor/ceiling color invalid:", line));
		i++;
	}
	return (1);
}

unsigned long	convert_rgb_hex(int *rgb)
{
	unsigned long	res;

	res = ((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff);
	return (res);
}

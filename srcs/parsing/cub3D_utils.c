/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:35:28 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/09 21:02:39 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	err_msg(char *message1, char *message2)
{
	printf("Error\n");
	printf("%s", message1);
	if (message2)
		printf("%s\n", message2);
	else
		printf("\n");
	return (ERROR);
}

// helper that checks whether the path is a directory
int	ft_is_dir(const char *path)
{
	struct stat	stat_buf;

	if (stat(path, &stat_buf) != 0)
		return (0);
	return (S_ISDIR(stat_buf.st_mode));
}

int	count_occurences(char *str, char c)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

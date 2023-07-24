/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:35:28 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/24 16:46:48 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	err_msg(int n, ...)
{
	va_list	msg;

	printf("Error\n");
	va_start(msg, n);
	while (n-- > 0)
		printf("%s\n", va_arg(msg, char *));
	va_end(msg);
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
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int	correct_extension(const char *argv, char *ending)
{
	size_t		len;
	const char	*extension;

	len = ft_strlen(argv);
	extension = ft_strnstr(argv, ending, len);
	if (!extension || ft_strncmp(extension, ending, ft_strlen(ending) + 1))
        return(0);
	return (1);
}

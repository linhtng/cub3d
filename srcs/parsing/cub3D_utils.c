/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:35:28 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 19:50:27 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * err_msg() prints an error message to the standard error output and returns
 * ERROR.
 */
int	err_msg(char *message1, char *message2)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(message1, STDERR_FILENO);
	if (message2)
		ft_putendl_fd(message2, STDERR_FILENO);
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	return (ERROR);
}

/*
 * count_occurences() counts the number of occurences of the character c in
 * the parameter string.
 */
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

/*
 * free_arr() frees the memory allocated for the given array of strings.
 */
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

/*
 * arr_len() returns the length of the given array of strings,
 * i.e the number of strings in the array, excluding the NULL terminator.
 */
int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

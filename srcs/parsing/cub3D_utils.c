/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:35:28 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 14:08:32 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

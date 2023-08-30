/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:35:28 by thuynguy          #+#    #+#             */
/*   Updated: 2023/08/30 10:04:57 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	err_msg(char *message1, char *message2)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(message1, STDERR_FILENO);
	if (message2)
		ft_putendl_fd(message1, STDERR_FILENO);
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	return (ERROR);
}

// int	err_msg(char *message1, char *message2)
// {
// 	printf("Error\n");
// 	printf("%s", message1);
// 	if (message2)
// 		printf("%s\n", message2);
// 	else
// 		printf("\n");
// 	return (ERROR);
// }

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

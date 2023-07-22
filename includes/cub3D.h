/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:19:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/22 20:59:39 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define ERROR -1
# define FLOOR 1
# define CEILING 2

typedef struct s_elem
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor_colors[3];
	int		ceiling_colors[3];
	int		filled_elem;
}	t_elem;

typedef struct s_scene
{
	int			height;
	int			width;
	char		**array;
	t_elem		elems;
	int			err_flag;
}	t_scene;

/* cub3D_utils */
int		correct_extension(const char *argv, char *ending);
int		err_msg(char *message);
int		count_occurences(char *str, char c);
int		ft_is_dir(const char *path);
int		arr_len(char **arr);
void	free_arr(char **arr);

/* cub3D_map */
int		get_map(int fd, t_scene *scene);

/* cub3D_debug */
void	print_arr(char **arr);
void	print_scene(t_scene *scene);

#endif


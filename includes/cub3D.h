/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:19:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/26 20:30:33 by thuynguy         ###   ########.fr       */
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
	int		fl_colors[4];
	int		c_colors[4];
	int		filled_elem;
}	t_elem;

typedef struct s_map
{
	int			height;
	int			width;
	char		**array;
}	t_map;

typedef struct s_scene
{
	int			len;
	char		**array;
	t_map		map;
	t_elem		elems;
	int			err_flag;
}	t_scene;

/* cub3D_utils */
int 	check_input_file(char *argv, int fd, char *extension);
int		correct_extension(const char *argv, char *ending);
int		err_msg(int n, ...);
int		count_occurences(char *str, char c);
int		ft_is_dir(const char *path);
int		arr_len(char **arr);
void	free_arr(char **arr);

/* cub3D_map */
int		get_scene_data(int fd, t_scene *scene);

/* cub3D_map_elems */
int		get_scene_elem(t_scene *scene, char *scene_line);

/* cub3D_map_content */
int		get_map_content(char **scene_arr, t_scene *scene, int i);

/* cub3D_debug */
void	print_arr(char **arr);
void	print_scene(t_scene *scene);

#endif


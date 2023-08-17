/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:44:57 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/16 17:41:09 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <mlx.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define ERROR -1
# define FLOOR 1
# define CEILING 2
# define SPACE '_'
# define VISITED '1'
# define DEBUG 0

typedef struct s_elem
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
	int					fl_rgb[4];
	int					c_rgb[4];
	unsigned	int	floor_color;
	unsigned	int	ceiling_color;
	int					filled_elem;
}	t_elem;

typedef struct s_map
{
	int			height;
	int			width;
	char		**grid;
	char		**flood;
	char		**visited;
}	t_map;

//change to floats?
typedef struct s_vector
{
	float	x;
	float	y;
	unsigned int	color;
}				t_vector;

/* struct to track location and direction of player*/
typedef struct s_player
{
	struct s_vector		location;
	// struct s_img_data	*player_img;
	float				angle;
	struct s_vector		d;
	char				spawn;
	// float				distance_to_pane;// calculate based on field of vison and projection pane dimensions
	// float				height; removed for now from intialization of player ^ as well
}				t_player;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img_data;

//TODO move minimap things to bouus version
typedef struct s_cubed
{
	struct s_scene		*scene;
	struct s_raycast	*raycast_info;
	void				*mlx;
	void				*window;
	struct s_img_data	*minimap_img;
	struct s_img_data	*mini_player_img;//player and rays drawn to this for minimap
	unsigned int		dirty_images;
} 				t_cubed;

typedef struct s_scene
{
	int			len;
	char		**array;
	t_map		map;
	t_elem		elems;
	t_player	player;
	int			err_flag;
	t_img_data	*dir[4];
}	t_scene;

/* cub3D_main */
void	init_scene(t_scene *scene);

/* cub3D_utils */
int 	check_input_file(char *argv, int fd, char *extension);
int		err_msg(char *message1, char *message2);
int		count_occurences(char *str, char c);
int		ft_is_dir(const char *path);
int		arr_len(char **arr);
void	free_arr(char **arr);

/* cub3D_parsing_utils */
int				correct_extension(const char *argv, char *ending);
unsigned int   convert_rgb_hex(int *rgb);
int				check_rgb_valid(t_scene *scene, char *line);
void			free_scene_data(t_scene *scene);

/* cub3D_map */
int		get_scene_data(int fd, t_scene *scene);

/* cub3D_map_elems */
int		get_scene_elem(t_scene *scene, char *scene_line);

/* cub3D_map_content */
int		get_map_content(char **scene_arr, t_scene *scene, int i);

/* cub3D_map_valid */
int		valid_walls(t_scene *scene, char **map);
void	ft_flood(int y, int x, t_scene *scene);
int		ft_arrdup(char **map, t_scene *scene);
int		empty_map(t_scene *scene);

/* cub3D_debug */
void	print_arr(char **arr);
void	print_scene(t_scene *scene);
void	mass_test_maps(int argc, char **argv);

#endif
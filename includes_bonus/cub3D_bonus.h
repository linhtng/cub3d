/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:44:57 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/26 18:30:50 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* MINI MAP DEFINES */
# define MINI_MAP_CELL 16
# define MINI_MAP_RADIUS 112
# define MINI_MAP_DIAMETER 224

/* IMAGE POSITIONING DEFINES */
# define MINIMAP_POS_X 60
# define MINIMAP_POS_Y 763
# define RAYCAST_Y 58

/* BONUS MAP CHARACTERS */
# define BONUS_CHAR 'B'
# define VALID_CHARS "01NSEWCDO "
# define MAP_CONTENT "0NSEWCDO"
# define HITABLE_MAP_VAL "1D"
# define INTERACTION_DISTANCE 13
# define INTERACTABLE_HERE "D"
# define INTERACTABLE_NEARBY "DO"
# define ANIMATION_FRAME 10
# define NUM_KEY 8
# define NUM_ELEMS 9

# include "../includes/cub3D.h"

typedef struct s_reward
{
	struct s_vector		pos;
	int					animated_frame;
}					t_reward;

enum	e_keys_pressed
{
	W_PRESSED,
	S_PRESSED,
	A_PRESSED,
	D_PRESSED,
	LEFT_PRESSED,
	RIGHT_PRESSED,
	ESC_PRESSED,
	SPACE_BAR
};

typedef struct s_cubed_bonus
{
	struct s_scene		*scene;
	struct s_raycast	*raycast_info;
	void				*mlx;
	void				*window;
	unsigned int		dirty_images;
	struct s_img_data	*minimap_img;
	struct s_img_data	*mini_player_img;
	struct s_img_data	*frame_img;
	int					keys[NUM_KEY];
	int					key_pressed;
	int					animated_frame;
}						t_cubed_bonus;

typedef struct s_elem_bonus
{
	char	*floor;
	char	*ceiling[3];
	char	*door;
}	t_elem_bonus;

typedef struct s_scene_bonus
{
	int				len;
	char			**array;
	t_map			map;
	t_elem			elems;
	t_player		player;
	int				err_flag;
	t_img_data		*texture[4];
	t_elem_bonus	bonus_elems;
	t_img_data		*bonus_textures[3];//add all bonus textures here, 0 texture is door, 1 is floor, 2 is ceiling
	t_img_data		*bonus_ceiling[4];
}					t_scene_bonus;

typedef struct s_bham_info
{
	struct s_vector	deltas;
	int				x_slope;
	int				y_slope;
	int				decision;
	int				d2;
}					t_bham_info;

typedef struct s_draw_info
{
	float		height;
	int			dir;
	int			project_x;          
	int			project_y;
	int			floor_start;
	int			material_hit;
	t_vector	tex;
}				t_draw_info;

enum	e_legend
{
	OPEN_SPACE = 0,
	NO_VALUE = ' ',
	WALL = 1,
	// FLOODED_WALL = 'B',
	DOOR_OPEN = 'O',
	DOOR_CLOSED = 'D'
};

enum	e_bonus_keys
{
	INTERACT = 49
};

/* ft_bresenham.c */
void	ft_bresenham_clipped(t_vector one, t_vector two, t_img_data *img);

/* draw minimap */
void	draw_minimap(t_cubed *cubed);
void	draw_minimap_rays(t_cubed_bonus *cubed, t_ray_calc *ray_info);

/* draw_player.c */
void	draw_mini_player(t_cubed *cubed);

/* cub3D_texture_bonus.c */
void	b_draw_textured_walls(t_cubed *cubed, t_ray_calc *ray, t_draw_info *d_info);

/* minimap_grid_bonus */
void	get_bonus_grid(t_scene *scene);

/* interact_bonus.c */
void	check_interaction(t_cubed_bonus *cubed);

/* handle_press_bonus.c */
int		handle_press_bonus(int key_code, t_cubed *cubed);

/* debug */
void	print_scene_bonus(t_scene_bonus *scene);

#endif

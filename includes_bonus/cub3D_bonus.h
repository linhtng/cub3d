/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:44:57 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 18:56:56 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define MINI_MAP_CELL 16
# define MINI_MAP_RADIUS 112
# define MINI_MAP_DIAMETER 224
# define MINIMAP_POS_X 60
# define MINIMAP_POS_Y 763
# define RAYCAST_Y 58
# define BONUS_CHAR 'B'
# define VALID_CHARS "01NSEW "
# define ANIMATION_FRAME 100

# include "../includes/cub3D.h"

typedef struct s_reward
{
	struct s_vector		pos;
	int					animated_frame;
}					t_reward;

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
	struct s_img_data	*reward_img;
	struct s_reward		reward;
}						t_cubed_bonus;

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
	float		line_height;
	int			dir;
	int			project_x;
	int			project_y;
	int			floor_start;
	t_vector	texture;
}				t_draw_info;

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

#endif

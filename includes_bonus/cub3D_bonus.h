/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:44:57 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/22 10:44:01 by jebouche         ###   ########.fr       */
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

# include "../includes/cub3D.h"

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

#endif
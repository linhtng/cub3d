/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:44:57 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/18 17:58:10 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H


# define MINI_MAP_CELL 32
# define MINI_MAP_RADIUS 112
# define MINI_MAP_DIAMETER 224

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
} 				t_cubed_bonus;

typedef	struct s_bham_info
{
	struct s_vector	deltas;
	int				x_slope;
	int				y_slope;
	int				decision;
	int				d2;
}				t_bham_info;

/* ft_bresenham.c */
void	ft_bresenham(t_vector one, t_vector two, t_img_data *img);

/* draw minimap */
void	draw_minimap(t_cubed *cubed);

/* draw_player.c */
void	draw_mini_player(t_cubed *cubed);

#endif
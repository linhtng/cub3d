/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:21:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 09:19:53 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAYCAST_BONUS_H
# define FT_RAYCAST_BONUS_H

/* for printf */
# include <stdio.h>
# include <math.h>
/* for minilibx */
# include <mlx.h>
# include <stdlib.h>
/* for write */
# include <unistd.h> 

// # include "cub3D_bonus.h"// take out once the combine happens

// # define CELL_SIZE 32
// # define TEXTURE_SIZE 64
// # define WIN_WIDTH 1920
// # define WIN_HEIGHT 1080
// # define PROJECTION_WIDTH 1366
// # define PROJECTION_HEIGHT 768
// # define MAX_DOF 10000
// # define FOV 60
// # define TRUE 1
// # define FALSE 0
// # define TRANSPARENT (unsigned int) 0x00ffffff

// enum	e_keys
// {
// 	FORWARD = 13,
// 	BACK = 1,
// 	LEFT = 0,
// 	RIGHT = 2,
// 	TURN_LEFT = 123,
// 	TURN_RIGHT = 124,
// 	ESC = 53
// };

// enum	e_diections
// {
// 	NORTH,
// 	SOUTH,
// 	EAST,
// 	WEST
// };

// typedef struct s_raycast
// {
// 	struct s_img_data	*r_img;
// 	struct s_img_data	*background_img;
// 	struct s_vector		center_of_projection;
// 	float				angle_between_rays;
// 	float				distances[PROJECTION_WIDTH];//maybe don't care about this until you are finding the intersections
// }			t_raycast;

// //TODO move minimap things to bouus version
// /* typedef struct s_cubed
// {
// 	struct s_scene		*scene;
// 	struct s_raycast	*raycast_info;
// 	void				*mlx;
// 	void				*window;
// 	struct s_img_data	*minimap_img;
// 	struct s_img_data	*mini_player_img;//player and rays drawn to this for minimap
// 	unsigned int		dirty_images;
// } 				t_cubed; */

// typedef	struct s_bham_info
// {
// 	struct s_vector	deltas;
// 	int				x_slope;
// 	int				y_slope;
// 	int				decision;
// 	int				d2;
// }				t_bham_info;

// typedef struct s_ray_calc
// {
// 	float			angle;
// 	struct s_vector	h_map;
// 	struct s_vector	h_grid;
// 	struct s_vector	v_map;
// 	struct s_vector	v_grid;
// 	float			tan;
// 	float			cotan;
// 	char			shortest;
// 	float			distance;
// 	struct s_vector	vd;
// 	struct s_vector	hd;
// }					t_ray_calc;

// /* draw minimap */
// void	draw_minimap(t_cubed *cubed, t_scene *scene);

// /* ft_bresenham.c */
// void	ft_bresenham(t_vector one, t_vector two, t_img_data *img);

// /* drawing_utils1 */
// void	my_put_line_h(t_img_data *data, t_vector *start, int len);
// void	my_put_line_v(t_img_data *data, t_vector *start, int len);
// void	my_put_grid(t_img_data *data, t_vector *start, int len, int height);//change args
// void	my_put_square(t_img_data *data, t_vector start, int len);
// void	my_put_rectangle(t_img_data *data, t_vector start, int len, int height);

// /* key hook handling */
// int		handle_press(int key_code, t_cubed *cubed);

// /* program exit functions */
// int		mlx_close(t_cubed *cubed, int exit_code, char *exit_msg);

// /* calculate_rays.c */
// void	shoot_one_ray_horizontal(t_cubed *cubed, t_ray_calc *ray);
// void	shoot_one_ray_vertical(t_cubed *cubed, t_ray_calc *ray);
// float	deg_to_rad(float degrees);
// float	correct_degrees(float degrees);
// void	cast_rays(t_cubed *cubed);

// /* draw_raycast_view.c */
// void	draw_background(t_cubed *cubed);
// // void	draw_view(t_cubed *cubed, float dist, int x, char side);
// void	draw_view(t_cubed *cubed, t_ray_calc *ray_info, int x);

// /* ft_images */
// t_img_data	*get_new_image(t_cubed *cubed, int width, int height);
// t_img_data	*get_new_xpm_image(t_cubed *cubed, char *file_path);
// void		refresh_images(t_cubed *cubed);

// /* utils_2.c */
// float	deg_to_rad(float degrees);
// float	correct_degrees(float degrees);
// float	get_distance(t_vector *player, t_vector *wall_hit);

// /* setup_player.c */
// void	setup_player(t_cubed *cubed);

// /* player_move.c */
// void	turn_player(t_cubed *cubed, int key_code);
// void	move_forward_backward(t_cubed *cubed, int key_code);
// void	move_right_left(t_cubed *cubed, int	key_code);

// /* draw_player.c */
// void	draw_mini_player(t_cubed *cubed);

// /* redraw.c */
// void	redraw(t_cubed *cubed);

// /* setup_cubed.c */
// void	setup_cubed(t_cubed *cubed);

// /* setup_scene */
// void	setup_scene(t_cubed *cubed, t_scene *scene);
// void	setup_raycast(t_cubed *cubed, t_raycast *raycast_info);

// /* ray_cast_main.c */
// int		raycast_start(t_scene *scene);

// /* cub3D_texture */
// void			load_texture(t_scene *scene, t_cubed *cubed);
// unsigned int	mlx_pixel_get(t_img_data *data, int x, int y);
// void			ft_pixel_put(t_img_data *data, int x, int y, unsigned int color);
// void			draw_textured_walls(t_cubed *cubed, int x, t_ray_calc *ray, int dir);

#endif
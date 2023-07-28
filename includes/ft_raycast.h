/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:21:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/28 10:19:23 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAYCAST_H
# define FT_RAYCAST_H

/* for printf */
# include <stdio.h>
# include <math.h>
/* for minilibx */
# include <mlx.h>
# include <stdlib.h>
/* for write */
# include <unistd.h> 

# include "cub3D.h"//

# define CELL_SIZE 32
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define PROJECTION_WIDTH 320
# define PROJECTION_HEIGHT 200
# define MAX_DOF 8
# define FOV 60

enum	e_keys
{
	FORWARD = 13,
	BACK = 1,
	LEFT = 0,
	RIGHT = 2,
	TURN_LEFT = 123,
	TURN_RIGHT = 124,
	ESC = 53
};

//change to floats?
typedef struct s_vector
{
	float	x;
	float	y;
	int	color;
}				t_vector;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

/* struct to track location and direction of player*/
typedef struct s_player
{
	struct s_vector		location;
	// struct s_img_data	*player_img;
	float				angle;
	struct s_vector		d;
	float				distance_to_pane;// calculate based on field of vison and projection pane dimensions
	float				height;
}				t_player;

typedef struct s_raycast
{
	struct s_img_data	*r_img;
	float				center_of_projection;
	float				angle_between_rays;
	float				distances[PROJECTION_WIDTH];//maybe don't care about this until you are finding the intersections
}			t_raycast;

typedef struct s_cubed
{
	struct s_scene		*scene;
	struct t_raycast	*raycast_info;
	void				*mlx;
	void				*window;
	struct s_img_data	*img;//for minimap currently
	struct s_player		player;
	struct s_img_data	*player_img;//player and rays drawn to this for minimap
} 				t_cubed;

typedef	struct s_bham_info
{
	struct s_vector	deltas;
	int				x_slope;
	int				y_slope;
	int				decision;
	int				d2;
}				t_bham_info;



typedef struct s_ray_calc
{
	float			angle;
	int				dof;
	struct s_vector	h_map;
	struct s_vector	h_grid; //move to hit check function only?
	struct s_vector	v_map;
	struct s_vector	v_grid;
	float			tan;
	float			cotan;
	float			h_distance;//?
	float			v_distance;//?
	struct s_vector	vd;
	struct s_vector	hd;
}					t_ray_calc;

/* draw minimap */
void	draw_minimap(t_cubed *cubed, t_scene *scene);

/* ft_bresenham.c */
void	ft_bresenham(t_vector one, t_vector two, t_img_data *img);
int		ft_abs(int val);

/* drawing_utils1 */
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
void	my_put_line_h(t_img_data *data, t_vector *start, int len);
void	my_put_line_v(t_img_data *data, t_vector *start, int len);
void	my_put_grid(t_img_data *data, t_vector *start, int len, int height);//change args
void	my_put_square(t_img_data *data, t_vector start, int len);

/* key hook handling */
int		handle_press(int key_code, t_cubed *cubed);

/* program exit functions */
int		mlx_close(t_cubed *cubed, int exit_code, char *exit_msg);

/* calculate_rays.c */
void	shoot_one_ray_horizontal(t_cubed *cubed, t_ray_calc *ray);
void	shoot_one_ray_vertical(t_cubed *cubed, t_ray_calc *ray);
float	deg_to_rad(float degrees);
float	correct_degrees(float degrees);
void	cast_rays(t_cubed *cubed);

/* draw_raycast_view.c */

#endif
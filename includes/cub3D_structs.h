/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:48:10 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/21 12:49:15 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

typedef struct s_cubed
{
	struct s_scene		*scene;
	struct s_raycast	*raycast_info;
	void				*mlx;
	void				*window;
	unsigned int		dirty_images;
}						t_cubed;

typedef struct s_vector
{
	float			x;
	float			y;
	unsigned int	color;
}					t_vector;

typedef struct s_elem
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
	int					fl_rgb[4];
	int					c_rgb[4];
	unsigned int		floor_color;
	unsigned int		ceiling_color;
	int					filled_elem;
}	t_elem;

typedef struct s_map
{
	int				height;
	int				width;
	char			**grid;
	char			**flood;
	char			**visited;
	struct s_vector	start;
	char			flood_old;
	char			flood_new;
}					t_map;

typedef struct s_player
{
	struct s_vector		location;
	float				angle;
	struct s_vector		d;
	char				spawn;
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

typedef struct s_scene
{
	int			len;
	char		**array;
	t_map		map;
	t_elem		elems;
	t_player	player;
	int			err_flag;
	t_img_data	*texture[4];
}	t_scene;

typedef struct s_raycast
{
	struct s_img_data	*r_img;
	struct s_img_data	*background_img;
	struct s_vector		center_of_projection;
	float				angle_between_rays;
}			t_raycast;

typedef struct s_ray_calc
{
	float			angle;
	struct s_vector	h_map;
	struct s_vector	h_grid;
	struct s_vector	v_map;
	struct s_vector	v_grid;
	float			tan;
	float			cotan;
	char			shortest;
	float			distance;
	struct s_vector	vd;
	struct s_vector	hd;
}					t_ray_calc;

#endif
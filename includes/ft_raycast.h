/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:21:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/19 18:25:32 by jebouche         ###   ########.fr       */
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

# define CELL_SIZE 32
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_vector
{
	int	x;
	int	y;
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

typedef struct s_cubed
{
	void				*mlx;
	void				*window;
	struct s_img_data	*img;
	struct s_vector		player;
	struct s_img_data	*player_img;
} 				t_cubed;

typedef	struct s_bham_info
{
	struct s_vector	deltas;
	int				x_slope;
	int				y_slope;
	int				decision;
	int				d2;
}				t_bham_info;

void	draw_minimap(t_cubed *cubed);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
void	ft_bresenham(t_vector one, t_vector two, t_cubed *cubed);

/* key hook handling */
int		handle_press(int key_code, t_cubed *cubed);



#endif
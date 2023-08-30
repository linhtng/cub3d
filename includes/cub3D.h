/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:39:58 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 15:26:55 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//TODO write what each are for, do we want printf still?
/* for printf */
# include <stdio.h>
/* for sin, cos, sqrt, etc*/
# include <math.h>
/* for minilibx */
# include <mlx.h>
/* for write, read, etc*/
# include <unistd.h>
/* for open */
# include <fcntl.h>

# include "cub3D_structs.h"
# include "cub3D_defines.h"
# include "libft.h"

/* init_scene */
void			init_scene(t_scene *scene);

/* cub3D_utils */
int				check_input_file(char *argv, int fd, char *extension);
int				err_msg(char *message1, char *message2);
int				count_occurences(char *str, char c);
int				arr_len(char **arr);
void			free_arr(char **arr);

/* cub3D_parsing_utils */
int				correct_extension(const char *argv, char *ending);
unsigned int	convert_rgb_hex(int *rgb);
int				check_rgb_valid(t_scene *scene, char *line);
void			free_scene_data(t_scene *scene);

/* cub3D_map */
int				get_scene_data(int fd, t_scene *scene);

/* cub3D_map_elems */
int				get_scene_elem(t_scene *scene, char *scene_line);

/* cub3D_map_content */
int				get_map_content(char **scene_arr, t_scene *scene, int i);

/* cub3D_map_valid */
int				check_island(t_scene *scene, char **grid);
void			ft_flood(int y, int x, t_scene *scene, char block);
int				big_frame_map(char **map, t_scene *scene);
int				empty_map(t_scene *scene);

/* cub3D_debug */
void			print_arr(char **arr);
void			print_scene(t_scene *scene);
void			mass_test_maps(int argc, char **argv);

/* drawing_utils1 */
void			my_put_line_h(t_img_data *data, t_vector *start, int len);
void			my_put_rectangle(t_img_data *data, t_vector start, int len, \
				int height);
unsigned int	ft_pixel_get(t_img_data *data, int x, int y);
void			ft_pixel_put(t_img_data *data, int x, int y, \
				unsigned int color);

/* key hook handling */
int				handle_press(int key_code, t_cubed *cubed);
int				close_window(t_cubed *cubed);

/* program exit functions */
int				mlx_close(t_cubed *cubed, int exit_code, char *exit_msg);

/* calculate_rays.c */
void			cast_rays(t_cubed *cubed);

/* draw_raycast_view.c */
void			draw_background(t_cubed *cubed);
void			draw_view(t_cubed *cubed, t_ray_calc *ray_info, int x);

/* ft_images */
t_img_data		*get_new_image(t_cubed *cubed, int width, int height);
t_img_data		*get_new_xpm_image(t_cubed *cubed, char *file_path);
void			refresh_images(t_cubed *cubed);

/* utils_2.c */
float			deg_to_rad(float degrees);
float			correct_degrees(float degrees);
float			get_distance(t_vector *player, t_vector *wall_hit);

/* setup_player.c */
void			setup_player(t_cubed *cubed);

/* player_move.c */
void			turn_player(t_cubed *cubed, int key_code);
void			move_forward_backward(t_cubed *cubed, int key_code);
void			move_right_left(t_cubed *cubed, int key_code);

/* redraw.c */
void			redraw(t_cubed *cubed);

/* setup_cubed.c */
void			setup_cubed(t_cubed *cubed);

/* setup_raycast */
void			setup_raycast(t_cubed *cubed, t_raycast *raycast_info);

/* ray_cast_main.c */
int				raycast_start(t_scene *scene);

/* cub3D_texture */
void			load_texture(t_scene *scene, t_cubed *cubed);
void			draw_textured_walls(t_cubed *cubed, int x, \
				t_ray_calc *ray, int dir);

#endif
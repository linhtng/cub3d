/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:14:11 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 09:23:37 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_BONUS_H
# define CUB3D_STRUCTS_BONUS_H


//TODO move minimap things to bouus version
typedef struct s_cubed_bonus
{
	struct s_scene		*scene;
	struct s_raycast	*raycast_info;
	void				*mlx;
	void				*window;
	unsigned int		dirty_images;
	struct s_img_data	*minimap_img;
	struct s_img_data	*mini_player_img;
} 				t_cubed_bonus;


#endif
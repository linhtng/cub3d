/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:19:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/18 16:19:32 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_texture
{
	char	*id;
	char	*path;
}	t_texture;

typedef struct s_scene
{
	int			lines;
	int			columns;
	char		**map;
	t_texture	*texture;
	int			*floor_color;
	int			*ceiling_color;
}	t_scene;

/* cub3D_utils */
void	correct_extension(const char *argv, int fd);
void	clean_exit(char *message);
int		count_occurences(char *str, char c);
int		ft_is_dir(const char *path);

#endif


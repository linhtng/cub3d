/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:46:17 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/30 15:00:17 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H
//TODO rmove debug?
/* PARSING DEFINES */
# define FLOOR 1
# define CEILING 2
# define DEBUG 0
# ifndef VALID_CHARS
#  define VALID_CHARS "01NSEW "
# endif

/* PROGRAM DEFINES */
# define WIN_WIDTH 1490
# define WIN_HEIGHT 1080
# define ERROR -1
# define TRUE 1
# define FALSE 0
# define PLAYER_SPEED 15

/* RAY CASTING DEFINES */
# define PROJECTION_WIDTH 1370
# define PROJECTION_HEIGHT 770
# define MAX_DOF 10000
# define FOV 60
# define CELL_SIZE 64
# define TEXTURE_SIZE 64

/* COLORS */
# define TRANSPARENT 0X00FFFFFF
# define RED 0XFF0000
# define LIGHT_GREY 0XA9A9A9
# define DARK_GREY 0X585858
# define PINK 0XFF9999
# define NAVY_BLUE 0X000785
# define DIM_GRAY 0X666666
# define TRANS_WHITE 0X99FFFFFF

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

enum	e_directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum	e_map_chars
{
	SPACE = '_',
	VISITED = '1',
	FLOODED_WALL = '2',
	EXPOSED = 'I'
};

#endif
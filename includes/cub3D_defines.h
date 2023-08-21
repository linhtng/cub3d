/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:46:17 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/21 16:12:16 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

/* PARSING DEFINES */
# define FLOOR 1
# define CEILING 2
# define SPACE '_'
# define VISITED '1'
# define FLOODED_WALL '2'
# define EXPOSED 'I'
# define DEBUG 0

/* PROGRAM DEFINES */
# define WIN_WIDTH 1490 //1920
# define WIN_HEIGHT 1080
# define ERROR -1
# define TRUE 1
# define FALSE 0
# define PANE_Y 1 //was this used, had to capitalize

/* RAY CASTING DEFINES */
# define PROJECTION_WIDTH 1370 //685//1370 //1366
# define PROJECTION_HEIGHT 770 // 385//770
# define MAX_DOF 10000
# define FOV 60
# define CELL_SIZE 64
# define TEXTURE_SIZE 64

/* COLORS */
# define TRANSPARENT (unsigned int) 0X00FFFFFF
# define BLACK (unsigned int) 0X000000
# define RED (unsigned int) 0XFF0000
# define LIGHT_GREY (unsigned int) 0XA9A9A9
# define DARK_GREY (unsigned int) 0X585858
# define PINK (unsigned int) 0XFF9999
# define NAVY_BLUE (unsigned int) 0X000785
# define YELLOW (unsigned int) 0X666666
# define TRANS_WHITE (unsigned int) 0X99FFFFFF

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

#endif
#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

/* PARSING DEFINES */
# define FLOOR 1
# define CEILING 2
# define SPACE '_'
# define VISITED '1'
# define DEBUG 0

/* PROGRAM DEFINES */
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define ERROR -1
# define TRUE 1
# define FALSE 0
# define pane_y 1

/* RAY CASTING DEFINES */
# define PROJECTION_WIDTH 1366
# define PROJECTION_HEIGHT 768
# define MAX_DOF 10000
# define FOV 60
# define CELL_SIZE 32
# define TEXTURE_SIZE 64
# define COLLISION_DISTANCE 0.25

/* COLORS */
# define TRANSPARENT (unsigned int) 0X00FFFFFF
# define BLACK (unsigned int) 0X000000
# define RED (unsigned int) 0XFF0000
# define LIGHT_GREY (unsigned int) 0XA9A9A9
# define DARK_GREY (unsigned int) 0X585858
# define PINK (unsigned int) 0XFF9999
# define NAVY_BLUE (unsigned int) 0X000785

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

#include "ft_raycast.h"
#include "cub3D.h"

/* 
	MAP SIZE * PROJECTION WIDTH / DISTANCE OF PLAYER FROM WALL = LINE HEIGHT
	center line height in projection pane ...
 */
void	draw_view(t_cubed *cubed, float dist, int x, char side)
{
	float		line_height;
	t_vector	start;

	if (side  == 'v')
		start.color = 0XFF0000;
	else
		start.color = 0XFFF000;
	line_height = CELL_SIZE * PROJECTION_HEIGHT / dist; 
	if (line_height > PROJECTION_HEIGHT)
		line_height = PROJECTION_HEIGHT;
	start.x = x;
	start.y = cubed->raycast_info->center_of_projection.y - line_height / 2;
	// printf("START XY for wall: %f, %f, center of projection %f\n", start.x, start.y, cubed->raycast_info->center_of_projection.y);
	//draw line
	my_put_line_v(cubed->raycast_info->r_img, &start, line_height);
}
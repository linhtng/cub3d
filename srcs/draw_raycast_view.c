
#include "ft_raycast.h"
#include "cub3D.h"

//only need to do once in the begining reuse the background as lonng as we dont raycast anything to it
void	draw_background(t_cubed *cubed)
{
	t_vector start;

	start.x = 0;
	start.y = 0;
	start.color = *cubed->scene->ceiling_color;
	while ((int) start.y < PROJECTION_HEIGHT) // +1?
	{
		if ((int) start.y > PROJECTION_HEIGHT / 2)
			start.color = *cubed->scene->floor_color;
		my_put_line_h(cubed->raycast_info->background_img, &start, PROJECTION_WIDTH);
		(start.y)++;
	}
}


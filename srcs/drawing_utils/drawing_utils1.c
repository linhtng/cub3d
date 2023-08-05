/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:30:49 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/31 11:38:07 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	my_put_line_h(t_img_data *data, t_vector *start, int len)
{
	int		i;
	int		x;

	i = 0;
	x = start->x;
	while (i < len)
	{
		my_mlx_pixel_put(data, start->x, start->y, start->color);
		start->x++;
		i++;
	}
	start->x = x;
}

void	my_put_line_v(t_img_data *data, t_vector *start, int len)
{
	int		i;
	int		y;

	i = 0;
	y = start->y;
	while (i < len)
	{
		my_mlx_pixel_put(data, start->x, start->y, start->color);
		start->y++;
		i++;
	}
	start->y = y;
}
void	my_put_grid(t_img_data *data, t_vector *start, int len, int height)
{
	int	i;
	t_vector	line_loc;

	i = 0;
	line_loc.x = start->x;
	line_loc.y = start->y;
	line_loc.color = 0x00FF0F;
	my_put_line_h(data, start, len * CELL_SIZE);
	my_put_line_v(data, start, height * CELL_SIZE);
	while (i < height)
	{
		line_loc.y += CELL_SIZE;
		my_put_line_h(data, &line_loc, len * CELL_SIZE);
		i++;
	}
	i = 0;
	line_loc.x = start->x;
	line_loc.y = start->y;
	while ( i < len)
	{
		line_loc.x += CELL_SIZE;
		my_put_line_v(data, &line_loc, height * CELL_SIZE);
		i++;
	}
}
void	my_put_square(t_img_data *data, t_vector start, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		my_put_line_v(data, &start, len);
		start.x++;
		i++;
	}
}
void	my_put_rectangle(t_img_data *data, t_vector start, int len, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		my_put_line_h(data, &start, len);
		start.y++;
		i++;
	}
}

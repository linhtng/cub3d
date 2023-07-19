/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:30:49 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/19 18:34:03 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
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
//too many args for this one
void	my_put_grid(t_img_data *data, t_vector *start, int	sq_size, int len, int height)
{
	int	i;
	t_vector	line_loc;

	i = 0;
	line_loc.x = start->x;
	line_loc.y = start->y;
	line_loc.color = 0x00FF0F;
	my_put_line_h(data, start, len * sq_size);
	my_put_line_v(data, start, height * sq_size);
	while (i < height)
	{
		line_loc.y += sq_size;
		my_put_line_h(data, &line_loc, len * sq_size);
		i++;
	}
	i = 0;
	line_loc.x = start->x;
	line_loc.y = start->y;
	while ( i < len)
	{
		line_loc.x += sq_size;
		my_put_line_v(data, &line_loc, height * sq_size);
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

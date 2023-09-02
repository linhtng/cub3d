/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:30:49 by jebouche          #+#    #+#             */
/*   Updated: 2023/09/02 16:13:09 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * ft_pixel_put() puts a pixel on the t_img_data *data held in data at the given
 * int x, int y coordinates. If the coordinates are outside the image, it does 
 * nothing.
*/
void	ft_pixel_put(t_img_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * 
			(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
 * ft_pixel_get() returns the color of the pixel at the given x, y coordinates
 * in the img held in data. If the coordinates are outside the image, it
 * returns the color RED.
*/
unsigned int	ft_pixel_get(t_img_data *data, int x, int y)
{
	unsigned int	dst;

	if (x >= data->width || x < 0 || y >= data->height || y < 0)
		return (RED);
	dst = *(unsigned int *)(data->addr + (y * data->line_length + x * 
				(data->bits_per_pixel / 8)));
	return (dst);
}

/*
 * my_put_line_v() draws a vertical line of length int len starting at the given
 * coordinates in t_vector *start. The color of the line is the color of the
 * start vector.
*/
void	my_put_line_h(t_img_data *data, t_vector *start, int len)
{
	int		i;
	int		x;

	i = 0;
	x = start->x;
	while (i < len)
	{
		ft_pixel_put(data, start->x, start->y, start->color);
		start->x++;
		i++;
	}
	start->x = x;
}

/*
 * my_put_line_v() draws a vertical line of length int len starting at the given
 * coordinates in t_vector *start. The color of the line is the color of the
 * start vector.
*/
void	my_put_rectangle(t_img_data *data, t_vector start, int len, int height)
{
	int	i;

	i = 0;
	start.y = start.y - height / 2;
	start.x = start.x - len / 2;
	while (i < height)
	{
		my_put_line_h(data, &start, len);
		start.y++;
		i++;
	}
}

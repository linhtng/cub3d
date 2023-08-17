/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:15:20 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/17 09:20:08 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_raycast_bonus.h"
#include "cub3D_bonus.h"
#include "cub3D.h"

static int	ft_abs(int val)
{
	if (val < 0)
		return (val * -1);
	return (val);
}

static void	set_up_bresenham(t_bham_info *line_info, t_vector *one, \
t_vector *two)
{
	line_info->deltas.x = ft_abs((int) two->x - (int) one->x);
	line_info->deltas.y = ft_abs((int) two->y - (int) one->y) * -1;
	line_info->x_slope = 1;
	if ((int) one->x > (int) two->x)
		line_info->x_slope = -1;
	line_info->y_slope = 1;
	if ((int) one->y > (int) two->y)
		line_info->y_slope = -1;
	line_info->decision = (int) line_info->deltas.x + (int) line_info->deltas.y;
	line_info->d2 = line_info->decision * 2;
}

void	ft_bresenham(t_vector one, t_vector two, t_img_data *img)
{
	t_bham_info	line_info;

	set_up_bresenham(&line_info, &one, &two);
	while (42)
	{
		ft_pixel_put(img, one.x, one.y, one.color);
		if ((int) one.x == (int) two.x && (int) one.y == (int) two.y)
			break ;
		line_info.d2 = line_info.decision * 2;
		if (line_info.d2 >= (int) line_info.deltas.y)
		{
			if (one.x == two.x)
				break ;
			line_info.decision += (int) line_info.deltas.y;
			one.x += line_info.x_slope;
		}
		if (line_info.d2 <= (int) line_info.deltas.x)
		{
			if ((int) one.y == (int) two.y)
				break ;
			line_info.decision += (int) line_info.deltas.x;
			one.y += (int) line_info.y_slope;
		}
	}
}

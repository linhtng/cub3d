/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:14:27 by jebouche          #+#    #+#             */
/*   Updated: 2023/08/09 13:24:48 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"

void	setup_scene(t_cubed *cubed, t_scene *scene)
{
	/*  hard coded scene info */
	scene->columns = 10;
	scene->lines = 7;
	//  char *MAP_2[] = {
	// 	"1111111111",
	// 	"1000000001",
	// 	"100000S001",
	// 	"1000110011",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1111111111"
	// 				};
	// scene->map = MAP_2;
	// int color1 = 0X91a3db;
	// int color2 = 0X91a358;
	// scene->ceiling_color = &color1;
	// scene->floor_color = &color2;
	cubed->scene = scene;
	/*  end of hard coded scene info */
}
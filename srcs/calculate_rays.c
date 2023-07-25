/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:49:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/25 17:51:26 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"
#include "cub3D.h"


float	correct_degrees(float degrees)
{
	if (degrees < 0)
		degrees += 360;
	else if (degrees >= 360)
		degrees -= 360;
	return (degrees);
}

float	deg_to_rad(float degrees)
{
	float	radians;

	radians  = degrees * (M_PI / 180);
	// printf("DEG: %f, RAD: %f", degrees, radians);//printed with correct values
	return (radians);
}


void	shoot_one_ray_horizontal(t_cubed *cubed, t_scene *scene, float angle)
{
	scene = (void *) scene;
	printf("HORIZONTAL \n");
	t_ray_calc ray;

	//INITAL shot
	//get y
	if (angle >=0 && angle < 180)//looking 'up'
		ray.map_intersection.y = cubed->player.location.y / CELL_SIZE * CELL_SIZE - 1;
	else
		ray.map_intersection.y = cubed->player.location.y / CELL_SIZE * CELL_SIZE + CELL_SIZE;
	//get x
	if (angle >=0 && angle < 180) // looking 'up'
		ray.map_intersection.x = cubed->player.location.x + (ft_abs(ray.map_intersection.y - cubed->player.location.y) / tan(deg_to_rad(angle)));//looking 'down' is wrong
	else
		ray.map_intersection.x = cubed->player.location.x - (ft_abs(cubed->player.location.y - ray.map_intersection.y) / tan(deg_to_rad(angle)));
	// TEST_PRINT
	printf("PLAYER LOCATION X,Y: %d,%d\n", cubed->player.location.x, cubed->player.location.y);//
	printf("FIRST INTERSECTION:\n");//
	printf("MAP X,Y: %d, %d\n", ray.map_intersection.x, ray.map_intersection.y);//
	if (angle >=0 && angle < 180)
		ray.y_inc = CELL_SIZE * -1; //moved out of while loop
	else 
		ray.y_inc = CELL_SIZE;
	if (angle >= 90 && angle < 270)
		ray.x_inc = ft_abs(CELL_SIZE / tan(deg_to_rad(angle))) * -1;//check for 0 vals
	else
		ray.x_inc = ft_abs(CELL_SIZE / tan(deg_to_rad(angle)));
	while (ray.map_intersection.y < CELL_SIZE * scene->lines && ray.map_intersection.y > 0)
	{	
		ray.map_intersection.y += ray.y_inc;
		ray.map_intersection.x += ray.x_inc;
		printf("NEXT INTERSECTION:\n");
		printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
	}
	cubed->player.location.color = 0xFFFFFF;//
	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);//

}
	// ray.dir_modifier.x = 1;
	// ray.dir_modifier.y = 1;
//TODO shoot rays to vericals
void	shoot_one_ray_vertical(t_cubed *cubed, t_scene *scene, float angle)
{
	scene = (void *) scene;
	printf("VERTICAL \n");
	t_ray_calc ray;

	//INITAL shot
	//get x
	if (angle >= 90 && angle < 270) // looking 'left'
		ray.map_intersection.x = (cubed->player.location.x / CELL_SIZE) * CELL_SIZE - 1;
	else
		ray.map_intersection.x = (cubed->player.location.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
	//get y
	// if (angle >=0 && angle < 180)//looking 'up'
		ray.map_intersection.y = cubed->player.location.y + ((cubed->player.location.x - ray.map_intersection.x) * tan(deg_to_rad(angle)));
	// else
		// ray.map_intersection.y = cubed->player.location.y + ((cubed->player.location.x - ray.map_intersection.x) * tan(deg_to_rad(angle)));
	// TEST_PRINT
	printf("PLAYER LOCATION X,Y: %d,%d\n", cubed->player.location.x, cubed->player.location.y);//
	printf("FIRST INTERSECTION:\n");//
	printf("MAP X,Y: %d, %d\n", ray.map_intersection.x, ray.map_intersection.y);//
// 	printf("MODIFIERS X: %i, Y: %i\n", ray.dir_modifier.x, ray.dir_modifier.y);//


	if (angle >= 90 && angle < 270)
		ray.x_inc = CELL_SIZE * -1; //moved out of while loop
	else 
		ray.x_inc = CELL_SIZE;
	if (angle >=0 && angle < 180)
		ray.y_inc = ft_abs(CELL_SIZE * tan(deg_to_rad(angle))) * -1;//check for 0 vals
	else
		ray.y_inc = ft_abs(CELL_SIZE * tan(deg_to_rad(angle)));

	// ray.x_inc = CELL_SIZE * ray.dir_modifier.x;
	// ray.y_inc = (ft_abs(CELL_SIZE * tan(deg_to_rad(angle)))) * ray.dir_modifier.y;//check for 0 vals///////
	while (ray.map_intersection.y < CELL_SIZE * scene->lines && ray.map_intersection.y > 0) //changed from x
	{	
		ray.map_intersection.y += ray.y_inc;
		ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;
		ray.map_intersection.x += ray.x_inc;
		ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);
		//PRINT to CHECK
		printf("NEXT INTERSECTION:\n");
		printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
	}
	cubed->player.location.color = 0xFF00FF;//
	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);//
}

// TODO: shoot one ray
// currently based on CELL SIZE for minimap
// void	shoot_one_ray_horizontal(t_cubed *cubed, t_scene *scene, float angle)
// {
// 	printf("HORIZONTAL \n");
// 	t_ray_calc ray;

// 	// scene = (void *) scene;
// 	ray.dir_modifier.x = 1;
// 	if (angle > 90 && angle < 270)
// 		ray.dir_modifier.x = -1;
// 	ray.dir_modifier.y = 1;
// 	if (angle < 180)//changed to be - for 'up'
// 		ray.dir_modifier.y = -1;
// 	if (ray.dir_modifier.y == 1) //find intersection
// 		ray.map_intersection.y = ((cubed->player.location.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE);
// 	else
// 		ray.map_intersection.y = (cubed->player.location.y / CELL_SIZE) * CELL_SIZE - 1; //removed cell size
// 	ray.y_inc = (cubed->player.location.y - ray.map_intersection.y);
// 	ray.map_intersection.x = cubed->player.location.x + (ray.y_inc / tan(deg_to_rad(angle)));//check about 0 values here
// 	ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;//TODO remove grid update
// 	ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);//TODO remove grid update
// 	printf("PLAYER LOCATION X,Y: %d,%d\n", cubed->player.location.x, cubed->player.location.y);//
// 	printf("FIRST INTERSECTION:\n");//
// 	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);//
// 	printf("MODIFIERS X: %i, Y: %i\n", ray.dir_modifier.x, ray.dir_modifier.y);//
	
	// ray.y_inc = CELL_SIZE * ray.dir_modifier.y; //moved out of while loop
	// ray.x_inc = (ft_abs(CELL_SIZE / tan(deg_to_rad(angle)))) * ray.dir_modifier.x;//check for 0 vals
	// while (ray.map_intersection.y < CELL_SIZE * scene->lines && ray.map_intersection.y > 0)
	// {	
	// 	ray.map_intersection.y += ray.y_inc;
	// 	ray.map_intersection.x += ray.x_inc;
	// 	printf("NEXT INTERSECTION:\n");
	// 	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
	// }
// 	ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;//TODO remove grid update
// 	ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);//TODO remove grid update
// 	cubed->player.location.color = 0xFFFF00;//
// 	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);//
// }
// //TODO shoot rays to vericals
// void	shoot_one_ray_vertical(t_cubed *cubed, t_scene *scene, float angle)
// {
// 	printf("VERTICAL \n");
// 	t_ray_calc ray;

// 	scene = (void *) scene;
// 	//determine direction
// 	ray.dir_modifier.x = 1;
// 	if (angle > 90 && angle < 270)
// 		ray.dir_modifier.x = -1;
// 	ray.dir_modifier.y = 1;
// 	if (angle < 180)//changed to be - for 'up'
// 		ray.dir_modifier.y = -1;
// 	//find first intersection
// 	if (ray.dir_modifier.x == 1)
// 		ray.map_intersection.x = ((cubed->player.location.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE);// should this just be -1?? ****changed to + CS
// 	else
// 		ray.map_intersection.x = (cubed->player.location.x / CELL_SIZE) * CELL_SIZE - 1;// causes segfault when I change this...

// 	ray.grid_intersection.x = ray.map_intersection.x / CELL_SIZE;
// 	ray.x_inc = ft_abs(cubed->player.location.x - ray.map_intersection.x);//do I want abs value here?/////* ray.dir_modifier.y
// 	printf("RAY INC X: %f\n", ray.x_inc);
// 	// ray.map_intersection.y = ray.x_inc * tan(deg_to_rad(angle));//check about 0 values here // does this work for decreases???
// 	ray.map_intersection.y = cubed->player.location.y + (ft_abs(ray.x_inc * tan(deg_to_rad(angle))) * ray.dir_modifier.y);//check about 0 values here // does this work for decreases???
// 	ray.grid_intersection.y = (ray.map_intersection.y / CELL_SIZE);
	
// 	//PRINT to CHECK
// 	printf("PLAYER LOCATION X,Y: %d,%d\n", cubed->player.location.x, cubed->player.location.y);
// 	printf("FIRST INTERSECTION:\n");
// 	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
// 	printf("MODIFIERS X: %i, Y: %i\n", ray.dir_modifier.x, ray.dir_modifier.y);
// 	cubed->player.location.color = 0xFF00FF;
// 	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);
// 	//TODO:save distances

// 	// find second intersection// repeat till grid == wall
// 	ray.x_inc = CELL_SIZE * ray.dir_modifier.x;
// 	ray.y_inc = (ft_abs(CELL_SIZE * tan(deg_to_rad(angle)))) * ray.dir_modifier.y;//check for 0 vals///////
// 	while (ray.map_intersection.y < CELL_SIZE * scene->lines && ray.map_intersection.y > 0) //changed from x
// 	{	
// 		ray.map_intersection.y += ray.y_inc;
// 		ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;
// 		ray.map_intersection.x += ray.x_inc;
// 		ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);
// 		//PRINT to CHECK
// 		printf("NEXT INTERSECTION:\n");
// 		printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
// 	}
// 		cubed->player.location.color = 0xFF00FF;
// 		ft_bresenham(cubed->player.location, ray.map_intersection, cubed);
// }




	// //PRINT to CHECK
	// printf("NEXT INTERSECTION:\n");
	// printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
	// }
////seems to be working, copied before cleaning up
// void	shoot_one_ray_horizontal(t_cubed *cubed, t_scene *scene, float angle)
// {
// 	t_ray_calc ray;

// 	// scene = (void *) scene;
// 	//determine direction
// 	ray.dir_modifier.x = 1;
// 	if (angle > 90 && angle < 270)
// 		ray.dir_modifier.x = -1;
// 	ray.dir_modifier.y = 1;
// 	if (angle < 180)//changed to be - for 'up'
// 		ray.dir_modifier.y = -1;
// 	//find first intersection
// 	if (ray.dir_modifier.y == 1)
// 		ray.map_intersection.y = ((cubed->player.location.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE);// should this just be -1?? ****changed to + CS
// 	else
// 		ray.map_intersection.y = (cubed->player.location.y / CELL_SIZE) * CELL_SIZE - CELL_SIZE;
// 	ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;
// 	ray.y_inc = (cubed->player.location.y - ray.map_intersection.y);//do I want abs value here?/////* ray.dir_modifier.y
// 	ray.map_intersection.x = cubed->player.location.x + (ray.y_inc / tan(deg_to_rad(angle)));//check about 0 values here
// 	ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);
// 	//PRINT to CHECK
// 	printf("PLAYER LOCATION X,Y: %d,%d\n", cubed->player.location.x, cubed->player.location.y);
// 	printf("FIRST INTERSECTION:\n");
// 	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
// 	printf("MODIFIERS X: %i, Y: %i\n", ray.dir_modifier.x, ray.dir_modifier.y);
// 	cubed->player.location.color = 0xFFFFFF;
// 	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);
// 	//TODO:save distances

// 	//find second intersection// repeat till grid == wall
// 	while (ray.map_intersection.y < CELL_SIZE * scene->lines && ray.map_intersection.y > 0)
// 	{	
// 	ray.y_inc = CELL_SIZE * ray.dir_modifier.y;
// 	ray.x_inc = (ft_abs(CELL_SIZE / tan(deg_to_rad(angle)))) * ray.dir_modifier.x;//check for 0 vals
// 	ray.map_intersection.y += ray.y_inc;
// 	ray.grid_intersection.y = ray.map_intersection.y / CELL_SIZE;
// 	ray.map_intersection.x += ray.x_inc;
// 	ray.grid_intersection.x = (ray.map_intersection.x / CELL_SIZE);
// 	//PRINT to CHECK
// 	printf("NEXT INTERSECTION:\n");
// 	printf("MAP X,Y: %d, %d, GRID X,Y: %i, %i\n", ray.map_intersection.x, ray.map_intersection.y, ray.grid_intersection.x, ray.grid_intersection.y);
// 	// cubed->player.location.color = 0x999911;
// 	ft_bresenham(cubed->player.location, ray.map_intersection, cubed);
// 	}
// }
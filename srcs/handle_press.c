/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:22:54 by jebouche          #+#    #+#             */
/*   Updated: 2023/07/19 18:23:06 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_raycast.h"

int	handle_press(int key_code, t_cubed *cubed)
{
	printf("KEY PRESSED: %i\n", key_code);
	if (key_code == 53)
		mlx_close(cubed, 0, "Normal exit");
	if (key_code == 123 || key_code == 124)
		printf("player should look some direction...\n");
	if (key_code == 13)
		printf("player whould go forward\n");
	if (key_code == 0)
		printf("player whould go left\n");
	if (key_code == 1)
		printf("player whould go backward\n");
	if (key_code == 2)
		printf("player whould go right\n");
	return (0);
}
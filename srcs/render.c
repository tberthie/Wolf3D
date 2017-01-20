/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/20 09:36:31 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>
#include <mlx.h>

static void		walls(int x, t_wolf *wolf)
{
	double	rx;
	double	ry;
	double	alpha;

	alpha = -FOV / 2 + FOV * x / WINX + wolf->angle;
	rx = cos(rad(alpha));
	ry = sin(rad(alpha));
}

void			render(t_wolf *wolf)
{
	int		x;

	x = 0;
	mlx_clear_window(wolf->mlx, wolf->win);
	while (x < WINX)
	{
		walls(x, wolf);
		x++;
	}
}

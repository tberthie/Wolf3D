/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/17 18:11:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>
#include <mlx.h>

int				intersect(double x, double y, double alpha)
{
	return (1);
}

int				horizontal(t_wolf *wolf, double *x, double alpha)
{
	double	y;
	int		i;

	y = floor(wolf->posy + (alpha > 180 && (wolf->posy != floor(wolf->posy))));
	*x = wolf->posx + (wolf->posy - y) / tan(rad(alpha));
	if (*x > wolf->line || *x < 0 || y * wolf->line > wolf->size || y < 0)
		return (0);
	while (!intersect(*x, y, alpha))
	{
		y += alpha > 180 ? 1 : -1;
		*x += 1 / tan(rad(alpha));
		if (*x > wolf->line || *x < 0 || y * wolf->line > wolf->size || y < 0)
			return (0);
	}
	return (1);
}

void			render(t_wolf *wolf)
{
	int		x;
	double	inter[2];
	double	alpha;
	double	dist;

	x = 0;
	dist = -1;
	while (x < WINX)
	{
		alpha = FOV - FOV * (x / WINX) + 15;
		alpha += (alpha < 0) * 360 - (alpha > 360) * 360;
		if (horizontal(wolf, &inter[0], alpha))
		{
			dist = fabs(wolf->posx - inter[0]) / cos(rad(FOV));
			printf("%f\n", inter[0]);
		}
		/*if (dist != -1)
			draw();*/
		x++;
	}
}

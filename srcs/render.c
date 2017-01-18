/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/18 16:22:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>
#include <mlx.h>

static double	horizontal(double alpha, t_wolf *wolf)
{
	double		x;
	double		y;

	y = floor(wolf->posy + (alpha > 180));
	x = wolf->posx + (wolf->posy - y) / tan(rad(alpha));

}

static void		walls(int x, t_wolf *wolf)
{
	double	hor;
	double	ver;
	double	alpha;

	alpha = -FOV / 2 + FOV * x / WINX + wolf->angle;
	while (alpha < 0 || alpha > 360)
		alpha += alpha < 0 ? 360 : -360;
	hor = horizontal(alpha, wolf);
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

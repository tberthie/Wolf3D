/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 19:28:51 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/26 00:17:22 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <math.h>

static char		set_mapcolor(int x, int y, t_wolf *wolf)
{
	double	px;
	double	py;

	px = wolf->posx + ((double)x - MINI / 2) / 10;
	py = wolf->posy + ((double)y - MINI / 2) / 10;
	if (px > 0 && py > 0 && px < wolf->line && py < wolf->size / wolf->line &&
	wolf->map[(int)(floor(px) + floor(py) * wolf->line)] != FLOOR)
		set_color(wolf, 255, 255, 255);
	else
		return (0);
	return (1);
}

void			render_minimap(t_wolf *wolf)
{
	int		x;
	int		y;

	y = 0;
	while (y < MINI)
	{
		x = 0;
		while (x < MINI)
		{
			if (sqrt(pow(x - (MINI / 2), 2) + pow(y - (MINI / 2), 2))
			< MINI / 2 && set_mapcolor(x, y, wolf))
				set_pixel(wolf, x, y);
			x++;
		}
		y++;
	}
	set_color(wolf, 0, 255, 255);
	set_pixel(wolf, MINI / 2, MINI / 2);
}

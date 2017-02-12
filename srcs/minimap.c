/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 19:28:51 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/12 20:22:03 by tberthie         ###   ########.fr       */
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
		SDL_SetRenderDrawColor(wolf->ren, 255, 255, 255, 255);
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
				SDL_RenderDrawPoint(wolf->ren, x, y);
			x++;
		}
		y++;
	}
	SDL_SetRenderDrawColor(wolf->ren, 0, 255, 255, 0);
	SDL_RenderDrawPoint(wolf->ren, MINI / 2, MINI / 2);
}

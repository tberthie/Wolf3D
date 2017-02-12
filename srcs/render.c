/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/12 17:15:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <math.h>

static void			render_floor(t_wolf *wolf)
{
	int		y;
	double	ratio;

	y = 0;
	while (y < WINY / 2 - wolf->pitch)
	{
		ratio = y / (WINY / 2);
		ratio = ratio > 1 ? 1 : ratio;
		SDL_SetRenderDrawColor(wolf->ren, FR * ratio, FG * ratio,
		FB * ratio, 255);
		SDL_RenderDrawLine(wolf->ren, 0, y + WINY / 2 + wolf->pitch, WINX, y
		+ WINY / 2 + wolf->pitch);
		y++;
	}
}

static void			render_sky(t_wolf *wolf)
{
	int		y;
	double	ratio;

	y = 0;
	while (y > -wolf->pitch)
	{
		ratio = 1 - y / (WINY / 2);
		ratio = ratio > 1 ? 1 : ratio;
		SDL_SetRenderDrawColor(wolf->ren, 0, 0, 125 * ratio, 255);
		SDL_RenderDrawLine(wolf->ren, 0, y + wolf->pitch, WINX,
		y + wolf->pitch);
		y++;
	}
}

void				render(t_wolf *wolf)
{
	int		x;
	double	alpha;

	SDL_SetRenderDrawColor(wolf->ren, 0, 0, 0, 0);
	SDL_RenderClear(wolf->ren);
	render_sky(wolf);
	render_floor(wolf);
	x = 0;
	while (x < WINX)
	{
		alpha = rad(wolf->angle + FOV / 2 - FOV * x / WINX);
		wolf->vx = cos(alpha);
		wolf->vy = -sin(alpha);
		walls(x, wolf);
		x++;
	}
	SDL_RenderPresent(wolf->ren);
}

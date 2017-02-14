/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/14 20:45:36 by tberthie         ###   ########.fr       */
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
		SDL_SetRenderDrawColor(wolf->ren, 150 * ratio, 150 * ratio,
		150 * ratio, 255);
		SDL_RenderDrawLine(wolf->ren, 0, y + WINY / 2 + wolf->pitch, WINX, y
		+ WINY / 2 + wolf->pitch);
		y++;
	}
}

static void			render_sky(t_wolf *wolf)
{
	int		y;
	double	ratio;

	y = WINY / 2;
	while (y > -wolf->pitch)
	{
		ratio = 1 - y / (WINY / 2);
		ratio = ratio > 1 ? 1 : ratio;
		SDL_SetRenderDrawColor(wolf->ren, 0, 0, 75 * ratio, 255);
		SDL_RenderDrawLine(wolf->ren, 0, y + wolf->pitch, WINX,
		y + wolf->pitch);
		y--;
	}
}

static void			render_crosshair(t_wolf *wolf)
{
	SDL_SetRenderDrawColor(wolf->ren, 0, 255, 0, 255);
	SDL_RenderDrawLine(wolf->ren, WINX / 2 - 5,
	WINY / 2, WINX / 2 + 5, WINY / 2);
	SDL_RenderDrawLine(wolf->ren, WINX / 2,
	WINY / 2 - 5, WINX / 2, WINY / 2 + 5);
}

void				render(t_wolf *wolf)
{
	int		x;
	double	alpha;

	SDL_SetRenderDrawColor(wolf->ren, 0, 0, 0, 0);
	SDL_RenderClear(wolf->ren);
	render_floor(wolf);
	render_sky(wolf);
	x = 0;
	while (x < WINX)
	{
		alpha = rad(wolf->angle + FOV / 2 - FOV * x / WINX);
		wolf->vx = cos(alpha);
		wolf->vy = -sin(alpha);
		walls(x, wolf);
		x++;
	}
	render_minimap(wolf);
	render_crosshair(wolf);
	SDL_RenderPresent(wolf->ren);
}

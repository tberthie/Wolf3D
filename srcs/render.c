/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/25 18:26:57 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <math.h>

static void		render_floor(t_wolf *wolf)
{
	int		y;
	double	ratio;

	y = 0;
	while (y < WINY / 2 - wolf->pitch)
	{
		ratio = y / (WINY / 2);
		ratio = ratio > 1 ? 1 : ratio;
		set_color(wolf, (int)(150 * ratio), (int)(150 * ratio),
		(int)(150 * ratio));
		draw_line(wolf, 0, y + WINY / 2 + wolf->pitch, WINX);
		y++;
	}
}

static void		render_sky(t_wolf *wolf)
{
	int		y;
	double	ratio;

	y = WINY / 2;
	while (y >= -wolf->pitch)
	{
		ratio = 1 - y / (WINY / 2);
		ratio = ratio > 1 ? 1 : ratio;
		set_color(wolf, 0, 0, (int)(75 * ratio));
		draw_line(wolf, 0, y + wolf->pitch, WINX);
		y--;
	}
}

static void			render_crosshair(t_wolf *wolf)
{
	set_color(wolf, 0, 255, 0);
	draw_line(wolf, WINX / 2 - 5, WINY / 2, 10);
	draw_line(wolf, WINX / 2, WINY / 2 - 5, -10);
}

void			render(t_wolf *wolf)
{
	int				x;
	double			alpha;
	SDL_Texture		*txt;

	wolf->img = SDL_CreateRGBSurface(0, WINX, WINY, 32, 0xff000000, 0x00ff0000,
	0x0000ff00, 0x000000ff);
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
//	render_minimap(wolf);
	render_crosshair(wolf);
	txt = SDL_CreateTextureFromSurface(wolf->ren, wolf->img);
	SDL_RenderCopy(wolf->ren, txt, 0, 0);
	SDL_DestroyTexture(txt);
	SDL_RenderPresent(wolf->ren);
	SDL_FreeSurface(wolf->img);
}

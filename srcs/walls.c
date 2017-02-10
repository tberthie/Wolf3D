/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 22:27:56 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/10 17:22:49 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>

static double			dist_hor(t_wolf *wolf, double vx, double vy)
{
	double	x;
	double	y;
	int		pos;

	y = floor(wolf->posy) + (vy > 0);
	x = wolf->posx + fabs(y - wolf->posy) * vx / fabs(vy);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (!is_wall(wolf->map[(pos = (int)(floor(x) + (y - (vy < 0))
	* wolf->line))]))
	{
		x += vx / fabs(vy);
		y += (vy < 0 ? -1 : 1);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	wolf->pos[0] = pos;
	wolf->ratio[0] = (vy > 0) ? 1 - fabs(x - floor(x)) : x - floor(x);
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static double			dist_ver(t_wolf *wolf, double vx, double vy)
{
	double	x;
	double	y;
	int		pos;

	x = floor(wolf->posx) + (vx > 0);
	y = wolf->posy + fabs(x - wolf->posx) * vy / fabs(vx);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (!is_wall(wolf->map[(pos = (int)(x - (vx < 0) + floor(y)
	* wolf->line))]))
	{
		x += (vx > 0 ? 1 : -1);
		y += vy / fabs(vx);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	wolf->pos[1] = pos;
	wolf->ratio[1] = (vx < 0) ? 1 - fabs(y - floor(y)) : y - floor(y);
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static void				draw_wall(int x, double dx, t_wolf *wolf)
{
	SDL_Rect		dst;
	SDL_Rect		src;
	double			ratio;
	int				height;

	ratio = dx > 4 ? 255 * (4 / dx) : 255;
	height = wolf->dste / (dx * cos(rad(-FOV / 2 + FOV * x / WINX)));
	src.x = *wolf->ratio * BMP;
	src.y = 0;
	src.w = 1;
	src.h = BMP;
	dst.x = x;
	dst.y = WINY / 2 - height / 2 + wolf->pitch;
	dst.w = 1;
	dst.h = height;
	if (find_texture(wolf))
	{
		SDL_SetTextureColorMod(wolf->tx, ratio, ratio, ratio);
		SDL_RenderCopy(wolf->ren, wolf->tx, &src, &dst);
	}
	else
	{
		SDL_SetRenderDrawColor(wolf->ren, ratio, ratio, ratio, 255);
		SDL_RenderDrawRect(wolf->ren, &dst);
	}
	draw_floor(wolf, WINY / 2 + height / 2 + wolf->pitch, x);
}

void					walls(int x, t_wolf *wolf, double vx, double vy)
{
	double	dx;
	double	dy;

	dx = dist_hor(wolf, vx, vy);
	dy = dist_ver(wolf, vx, vy);
	if (dx == -1 || (dy != -1 && dy < dx))
	{
		dx = dy;
		wolf->pos[0] = wolf->pos[1];
		wolf->ratio[0] = wolf->ratio[1];
	}
	if (dx > 0)
		draw_wall(x, dx, wolf);
}

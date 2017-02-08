/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 22:27:56 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/08 10:31:31 by tberthie         ###   ########.fr       */
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
	while (wolf->map[(pos = (int)(floor(x) + (y - (vy < 0)) * wolf->line))]
	!= WALL)
	{
		x += vx / fabs(vy);
		y += (vy < 0 ? -1 : 1);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	wolf->pos[0] = pos;
	wolf->ratio[0] = (vy < 0) ? x - floor(x) : 1 - x - floor(x);
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
	while (wolf->map[(pos = (int)(x - (vx < 0) + floor(y) * wolf->line))]
	!= WALL)
	{
		x += (vx > 0 ? 1 : -1);
		y += vy / fabs(vx);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	wolf->pos[1] = pos;
	wolf->ratio[1] = (vx > 0) ? y - floor(y) : 1 - y - floor(y);
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static void				draw_wall(int x, int beg, int height, t_wolf *wolf)
{
/*	SDL_Texture		*tx;
	SDL_Rect		SrcR;
	SDL_Rect		DestR;

	SrcR.x = *wolf->ratio * 16;
	SrcR.y = 0;
	SrcR.w = 1;
	SrcR.h = (height / WINY) * 16;
	DestR.x = x;
	DestR.y = beg;
	DestR.w = 1;
	DestR.h = height;

	tx = SDL_CreateTextureFromSurface(wolf->ren, SDL_LoadBMP("Wall1.bmp"));
	SDL_RenderCopy(wolf->ren, tx, &SrcR, &DestR);*/
	SDL_Rect	r;
	double		ratio;

	r.h = height;
	r.x = x;
	r.y = beg;
	r.w = 1;
	height > WINY ? height = WINY : 0;
	ratio = 255 * height / WINY;
	SDL_SetRenderDrawColor(wolf->ren, ratio, ratio, ratio, 255);
	SDL_RenderFillRect(wolf->ren, &r);
}

void					walls(int x, t_wolf *wolf, double vx, double vy)
{
	double	dx;
	double	dy;
	int		height;

	dx = dist_hor(wolf, vx, vy);
	dy = dist_ver(wolf, vx, vy);
	if (dx == -1 || (dy != -1 && dy < dx))
	{
		dx = dy;
		wolf->pos[0] = wolf->pos[1];
		wolf->ratio[0] = wolf->ratio[1];
	}
	if (dx > 0)
	{
		height = wolf->dste / (dx * cos(rad(-FOV / 2 + FOV * x / WINX)));
		draw_wall(x, WINY / 2 - height / 2 + wolf->pitch, height, wolf);
	}
}

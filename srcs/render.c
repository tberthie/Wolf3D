/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/07 19:24:20 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>

static double			dist_hor(t_wolf *wolf, double dir[4])
{
	double	x;
	double	y;

	y = floor(wolf->posy) + (dir[1] > 0);
	x = wolf->posx + fabs(y - wolf->posy) * dir[0] / fabs(dir[1]);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(int)(floor(x) + (y - (dir[1] < 0)) * wolf->line)] != WALL)
	{
		x += dir[0] / fabs(dir[1]);
		y += (dir[1] < 0 ? -1 : 1);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static double			dist_ver(t_wolf *wolf, double dir[4])
{
	double	x;
	double	y;

	x = floor(wolf->posx) + (dir[0] > 0);
	y = wolf->posy + fabs(x - wolf->posx) * dir[1] / fabs(dir[0]);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(int)(x - (dir[0] < 0) + floor(y) * wolf->line)] != WALL)
	{
		x += (dir[0] > 0 ? 1 : -1);
		y += dir[1] / fabs(dir[0]);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static void				walls(int x, t_wolf *wolf)
{
	double	vals[4];
	SDL_Rect r;

	vals[0] = cos(rad(wolf->angle + FOV / 2 - FOV * x / WINX));
	vals[1] = -sin(rad(wolf->angle + FOV / 2 - FOV * x / WINX));
	vals[2] = dist_hor(wolf, vals);
	vals[3] = dist_ver(wolf, vals);
	vals[2] == -1 || (vals[3] != -1 && vals[3] < vals[2]) ? vals[2] = vals[3] : 0;
	r.h = vals[2] > 0 ? 3 / (vals[2] * cos(rad(-FOV / 2 + FOV * x / WINX)))
	* wolf->dste : 0;
	r.x = x;
	r.y = WINY / 2 - r.h / 2;
	r.w = 1;
	SDL_RenderFillRect(wolf->ren, &r);
}

void					render(t_wolf *wolf)
{
	int		x;

	SDL_SetRenderDrawColor(wolf->ren, 0, 0, 0, 0);
	SDL_RenderClear(wolf->ren);
	SDL_SetRenderDrawColor(wolf->ren, 255, 255, 255, 255);
	x = 0;
	while (x < WINX)
		walls(x++, wolf);
	SDL_RenderPresent(wolf->ren);
}

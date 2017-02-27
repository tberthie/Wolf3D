/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 22:27:56 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 16:55:40 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>

static double	dist_hor(t_wolf *wolf, double vx, double vy)
{
	double	x;
	double	y;
	int		pos;

	y = floor(wolf->posy) + (vy > 0);
	x = wolf->posx + fabs(y - wolf->posy) * vx / fabs(vy);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(pos = (int)(floor(x) + (y - (vy < 0))
	* wolf->line))] == FLOOR)
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

static double	dist_ver(t_wolf *wolf, double vx, double vy)
{
	double	x;
	double	y;
	int		pos;

	x = floor(wolf->posx) + (vx > 0);
	y = wolf->posy + fabs(x - wolf->posx) * vy / fabs(vx);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(pos = (int)(x - (vx < 0) + floor(y)
	* wolf->line))] == FLOOR)
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

static void		textured_wall(int x, double ratio, int height, t_wolf *wolf)
{
	unsigned int	color;
	int				offset;
	int				y;
	int				i;

	y = WINY / 2 - height / 2 + wolf->pitch;
	i = y < 0 ? -y : 0;
	while (i < height && y + i < WINY)
	{
		offset = floor(*wolf->ratio * wolf->tx->pitch) +
		floor((double)i / (double)height * BMP) * wolf->tx->pitch;
		offset -= offset % wolf->tx->format->BytesPerPixel;
		color = *(unsigned int*)(wolf->tx->pixels + offset);
		set_color(wolf, (unsigned char)(color >> 16) * ratio,
		(unsigned char)(color >> 8) * ratio, (unsigned char)color * ratio);
		set_pixel(wolf, x, y + i++);
	}
}

static void		untextured_wall(int x, double ratio, int height, t_wolf *wolf)
{
	int		correction;
	int		y;

	y = WINY / 2 - height / 2 + wolf->pitch;
	correction = y < 0 ? -y : 0;
	if (y + height > WINY)
		height -= y + height - WINY;
	set_color(wolf, ratio * 255, ratio * 255, ratio * 255);
	draw_line(wolf, x, y + correction, -(height - correction));
}

void			walls(int x, t_wolf *wolf)
{
	double	dx;
	double	dy;

	dx = dist_hor(wolf, wolf->vx, wolf->vy);
	dy = dist_ver(wolf, wolf->vx, wolf->vy);
	if (dx == -1 || (dy != -1 && dy < dx))
	{
		dx = dy;
		wolf->pos[0] = wolf->pos[1];
		wolf->ratio[0] = wolf->ratio[1];
	}
	if (dx > 0)
	{
		if (find_texture(wolf))
			textured_wall(x, dx > 4 ? 4 / dx : 1, wolf->dste / (dx *
			cos(rad(-FOV / 2 + FOV * x / WINX))), wolf);
		else
			untextured_wall(x, dx > 4 ? 4 / dx : 1, wolf->dste / (dx *
			cos(rad(-FOV / 2 + FOV * x / WINX))), wolf);
	}
}

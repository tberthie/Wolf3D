/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/20 15:57:45 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>
#include <mlx.h>

static double			dist_y(t_wolf *wolf, double alpha)
{
	double	x;
	double	y;
	int		i;

	y = (int)(wolf->posy) + (alpha > R180);
	x = wolf->posx + (wolf->posy - y) / tan(alpha);
	if (x < 0 || y < 0 || x > wolf->line || y * wolf->line > wolf->size)
		return (-1);
	i = (y + (alpha > R180)) * wolf->line + floor(x);
	while (x && y && x != wolf->line &&
	y * wolf->line != wolf->size && wolf->map[i] != WALL)
	{
		y += alpha > R180 ? 1 : -1;
		x += 1 / tan(alpha);
		if (x < 0 || y < 0 || x > wolf->line || y * wolf->line > wolf->size)
			return (-1);
		i = (y + (alpha > R180)) * wolf->line + floor(x);
	}
	return (fabs(wolf->posx - x) / cos(alpha));
}

static double		dist_x(t_wolf *wolf, double alpha)
{
	double	x;
	double	y;
	int		i;

	x = (int)(wolf->posx) + (alpha < R90 || alpha > R270);
	y = wolf->posy + (wolf->posx - x) * tan(alpha);
	if (x < 0 || y < 0 || x > wolf->line || y * wolf->line > wolf->size)
		return (-1);
	i = y * wolf->line + floor(x) + (alpha < R90 || alpha > R270);
	while (x && y && x != wolf->line &&
	y * wolf->line != wolf->size && wolf->map[i] != WALL)
	{
		y += tan(alpha);
		x += alpha < R90 || alpha > R270 ? 1 : -1;
		if (x < 0 || y < 0 || x > wolf->line || y * wolf->line > wolf->size)
			return (-1);
		i = y * wolf->line + floor(x) + (alpha < R90 || alpha > R270);
	}
	return (fabs(wolf->posx - x) / cos(alpha));
}

static void			walls(int x, t_wolf *wolf)
{
	double	alpha;
	double	dst[2];
	int		height;
	int		y;

	alpha = rad(FOV - x / WINX * FOV + wolf->angle);
	dst[0] = dist_x(wolf, alpha);
	dst[1] = dist_y(wolf, alpha);
	dst[0] == -1 || (dst[1] != -1 && dst[0] > dst[1]) ? dst[1] = dst[0] : 0;
	height = 1 / (dst[0] * (cos(rad(alpha) - rad(FOV / 2)))) * wolf->dste;
	height < 0 ? height = 0 : 0;
	y = 0;
	while (y < WINY)
	{
		if (y < WINY / 2 - height / 2)
			mlx_pixel_put(wolf->mlx, wolf->win, x, y, 0x0000a0);
		else if (y < WINY / 2 + height / 2)
			mlx_pixel_put(wolf->mlx, wolf->win, x, y, 0xa0a0a0);
		else
			mlx_pixel_put(wolf->mlx, wolf->win, x, y, 0xffffff);
		y++;
	}
}

void				render(t_wolf *wolf)
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

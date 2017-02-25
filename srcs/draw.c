/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:19:19 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/25 18:27:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		set_pixel(t_wolf *wolf, int x, int y)
{
	unsigned int	*target;

	if (x < 0 || x > WINX || y < 0 || y > WINY)
		return ;
	target = wolf->img->pixels + (y * wolf->img->pitch + x * 4);
	*target = wolf->color;
}

void		draw_line(t_wolf *wolf, int x, int y, int off)
{
	char		rot;

	rot = off < 0;
	off = off < 0 ? -off : off;
	while (off-- >= 0)
	{
		set_pixel(wolf, x, y);
		x += !rot;
		y += rot;
	}
}

void		set_color(t_wolf *wolf, int r, int g, int b)
{
	unsigned int	color;

	color = 255;
	color |= (unsigned char)b << 8;
	color |= (unsigned char)g << 16;
	color |= (unsigned char)r << 24;
	wolf->color = color;
}

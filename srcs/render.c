/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/21 18:28:52 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>
#include <mlx.h>

static double			dist_x(t_wolf *wolf, double alpha)
{
	double	x;
	double	y;

	x = (int)(wolf->posx) + (alpha < 90 || alpha > 270);
	y = wolf->posy + (wolf->posx - x) * tan(rad(alpha));
	if (x < 0 || x > wolf->line || y < 0 || y > wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(int)(x - (alpha > 90 && alpha < 270) + floor(y)
	* wolf->line)] != WALL)
	{
		y += tan(rad(alpha));
		x += alpha < 90 || alpha > 270 ? 1 : -1;
		if (x < 0 || x > wolf->line || y < 0 || y > wolf->size / wolf->line)
			return (-1);
	}
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static double			dist_y(t_wolf *wolf, double alpha)
{
	double	x;
	double	y;

	y = (int)(wolf->posy) + (alpha > 180);
	x = wolf->posx + (wolf->posy - y) / tan(rad(alpha));
	if (x < 0 || x > wolf->line || y < 0 || y > wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(int)(floor(x) + (y - (alpha < 180))
	* wolf->line)] != WALL)
	{
		y += alpha > 180 ? 1 : -1;
		x += 1 / tan(rad(alpha));
		if (x < 0 || x > wolf->line || y < 0 || y > wolf->size / wolf->line)
			return (-1);
	}
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static void				walls(int x, t_wolf *wolf, char *pixels)
{
	double	alpha;
	double	dst[2];
	int		height;
	int		y;

	alpha = FOV / 2 - FOV * x / WINX + wolf->angle;
	while (alpha >= 360 || alpha < 0)
		alpha += alpha < 0 ? 360 : -360;
	dst[0] = dist_x(wolf, alpha);
	dst[1] = dist_y(wolf, alpha);
	dst[0] == -1 || (dst[1] != -1 && dst[1] < dst[0]) ? dst[0] = dst[1] : 0;
	height = *dst > 0 ? 3 / (*dst * cos(rad(-FOV / 2 + FOV * x / WINX))) *
	wolf->dste : 0;
	y = WINY / 2 - height / 2;
	pixels += y * wolf->ls + x * 4;
	while (y < WINY / 2 + height / 2)
	{
		pixels[0] = mlx_get_color_value(wolf->mlx, 0xffffff);
		pixels[1] = mlx_get_color_value(wolf->mlx, 0xffffff) >> 8;
		pixels[2] = mlx_get_color_value(wolf->mlx, 0xffffff) >> 16;
		pixels += wolf->ls;
		y++;
	}
}

void					render(t_wolf *wolf)
{
	int		x;
	void	*img;
	char	*pixels;

	img = mlx_new_image(wolf->mlx, WINX, WINY);
	pixels = mlx_get_data_addr(img, &wolf->bpp, &wolf->ls, &wolf->end);
	x = 0;
	mlx_clear_window(wolf->mlx, wolf->win);
	while (x < WINX)
		walls(x++, wolf, pixels);
	mlx_put_image_to_window(wolf->mlx, wolf->win, img, 0, 0);
	mlx_destroy_image(wolf->mlx, img);
}

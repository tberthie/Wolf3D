/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/07 17:38:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>
#include <mlx.h>

static double			dist_hor(t_wolf *wolf, double dir[4])
{
	double	x;
	double	y;

	y = floor(wolf->posy) + (dir[1] < 0);
	x = wolf->posx + fabs(y - wolf->posy) * dir[0] / fabs(dir[1]);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(int)(floor(x) + (y - (dir[1] > 0)) * wolf->line)] != WALL)
	{
		x += dir[0] / fabs(dir[1]);
		y += (dir[1] > 0 ? -1 : 1);
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
	y = wolf->posy + fabs(x - wolf->posx) * -dir[1] / fabs(dir[0]);
	if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
		return (-1);
	while (wolf->map[(int)(x - (dir[0] < 0) + floor(y) * wolf->line)] != WALL)
	{
		x += (dir[0] > 0 ? 1 : -1);
		y += -dir[1] / fabs(dir[0]);
		if (x <= 0 || y <= 0 || x >= wolf->line || y >= wolf->size / wolf->line)
			return (-1);
	}
	return (sqrt(pow(wolf->posx - x, 2) + pow(wolf->posy - y, 2)));
}

static void				walls(int x, t_wolf *wolf, char *pixels)
{
	double	vals[4];
	int		height;
	int		y;

	vals[0] = cos(rad(wolf->angle + FOV / 2 - FOV * x / WINX));
	vals[1] = sin(rad(wolf->angle + FOV / 2 - FOV * x / WINX));
	vals[2] = dist_hor(wolf, vals);
	vals[3] = dist_ver(wolf, vals);
	vals[2] == -1 || (vals[3] != -1 && vals[3] < vals[2]) ? vals[2] = vals[3] : 0;
	height = vals[2] > 0 ? 3 / (vals[2] * cos(rad(-FOV / 2 + FOV * x / WINX)))
	* wolf->dste : 0;
	height > WINY ? height = WINY : 0;
	y = WINY / 2 - height / 2;
	pixels += y * wolf->ls + x * 4;
	while (y < WINY / 2 + height / 2)
	{
		pixels[0] = mlx_get_color_value(wolf->mlx, 0xdddddd);
		pixels[1] = mlx_get_color_value(wolf->mlx, 0xdddddd) >> 8;
		pixels[2] = mlx_get_color_value(wolf->mlx, 0xdddddd) >> 16;
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
	mlx_string_put(wolf->mlx, wolf->win, 0, 0, 0xffffff, ft_itoa(wolf->angle));
	mlx_destroy_image(wolf->mlx, img);
}

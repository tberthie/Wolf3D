/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:09:57 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/07 15:50:53 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <unistd.h>
#include <mlx.h>
#include <math.h>

int			key(int code, t_wolf *wolf)
{
	if (code == 0)
		wolf->angle += 5;
	if (code == 2)
		wolf->angle -= 5;
	render(wolf);
	return (1);
}

void		run(t_wolf *wolf)
{
	wolf->mlx = 0;
	wolf->win = 0;
	if ((wolf->mlx = mlx_init()) &&
	(wolf->win = mlx_new_window(wolf->mlx, WINX, WINY, "Wolf3D")))
	{
		render(wolf);
		mlx_key_hook(wolf->win, key, wolf);
		mlx_loop(wolf->mlx);
	}
	!wolf->mlx ? write(2, "wolf3d: mlx failed to init\n", 27) :
	write(2, "wolf3d: failed to create window\n", 32);
}

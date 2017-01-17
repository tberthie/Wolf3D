/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:09:57 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/17 16:46:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <unistd.h>
#include <mlx.h>

void		run(t_wolf *wolf)
{
	if ((wolf->mlx = mlx_init()) &&
	(wolf->win = mlx_new_window(wolf->mlx, WINX, WINY, "Wolf3D")))
	{
		render(wolf);
		mlx_loop(wolf->mlx);
	}
	(!wolf->mlx) ? write(2, "wolf3d: mlx failed to init\n", 27) :
	write(2, "wolf3d: failed to create window\n", 32);
}

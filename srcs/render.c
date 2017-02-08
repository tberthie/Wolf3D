/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:51:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/08 01:03:47 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <math.h>

void					render(t_wolf *wolf)
{
	int		x;
	double	alpha;

	SDL_SetRenderDrawColor(wolf->ren, 0, 0, 0, 0);
	SDL_RenderClear(wolf->ren);
	x = 0;
	while (x < WINX)
	{
		alpha = rad(wolf->angle + FOV / 2 - FOV * x / WINX);
		walls(x, wolf, cos(alpha), -sin(alpha));
		x++;
	}
	SDL_RenderPresent(wolf->ren);
}

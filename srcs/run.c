/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:09:57 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/08 01:25:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <SDL.h>
#include <unistd.h>

static void		move(int dir, t_wolf *wolf)
{
	double	mx;
	double	my;

	if (dir == 0 || dir == 2)
	{
		mx = (dir == 0 ? 1 : -1) * cos(rad(wolf->angle)) / 20;
		my = (dir == 0 ? -1 : 1) * sin(rad(wolf->angle)) / 20;
	}
	else
	{
		mx = cos(rad(wolf->angle + (dir == 1 ? 90 : -90))) / 20;
		my = -sin(rad(wolf->angle + (dir == 1 ? 90 : -90))) / 20;
	}
	if (wolf->posx + mx >= 0 && wolf->posx + mx <= wolf->size / wolf->line &&
	wolf->map[(int)(floor(wolf->posx + mx) + floor(wolf->posy) * wolf->line)]
	!= WALL)
		wolf->posx += mx;
	if (wolf->posy + my >= 0 && wolf->posy + my <= wolf->size / wolf->line &&
	wolf->map[(int)(floor(wolf->posx) + floor(wolf->posy + my) * wolf->line)]
	!= WALL)
		wolf->posy += my;
}

static void		event(SDL_Event event, t_wolf *wolf)
{
	if (event.type == SDL_KEYDOWN)
	{
		event.key.keysym.sym == SDLK_ESCAPE ? wolf->status = 0 : 0;
		event.key.keysym.sym == SDLK_w ? move(0, wolf) : 0;
		event.key.keysym.sym == SDLK_a ? move(1, wolf) : 0;
		event.key.keysym.sym == SDLK_s ? move(2, wolf) : 0;
		event.key.keysym.sym == SDLK_d ? move(3, wolf) : 0;
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
		wolf->angle -= (double)(event.motion.xrel) / 15;
		wolf->pitch -= (double)(event.motion.yrel);
	}
	wolf->pitch > WINX ? wolf->pitch = WINX : 0;
	wolf->pitch < -WINX ? wolf->pitch = -WINX : 0;
}

void			run(t_wolf *wolf)
{
	SDL_Event		ev;
	unsigned int	lt;
	unsigned int	t;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		write(2, "wolf3d: SDL failed to init\n", 27);
	else if ((wolf->win = SDL_CreateWindow("Wolf3d", 0, 0, WINX, WINY,
	SDL_WINDOW_SHOWN)) && (wolf->ren = SDL_CreateRenderer(wolf->win, -1,
	SDL_RENDERER_ACCELERATED)))
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		t = SDL_GetTicks();
		while ((wolf->status))
		{
			lt = t;
			t = SDL_GetTicks();
			printf("FPS\t%f\n", 1.0 / ((double)(t - lt) / 1000.0));
			if (SDL_PollEvent(&ev))
				event(ev, wolf);
			wolf->status == 1 ? render(wolf) : menu(wolf);
		}
		SDL_DestroyWindow(wolf->win);
	}
	else
		write(2, "wolf3d: SDL failed to create window\n", 36);
	SDL_Quit();
}

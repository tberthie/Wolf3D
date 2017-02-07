/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:09:57 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/07 19:41:09 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <SDL.h>
#include <unistd.h>

static void		move(int dir)
{
	if (!dir)
	{

	}
}

static void		event(SDL_Event event, t_wolf *wolf)
{
	if (event.type == SDL_KEYDOWN)
	{
		event.key.keysym.sym == SDLK_ESCAPE ? wolf->running = 0 : 0;
		event.key.keysym.sym == SDLK_w ? move(0) : 0;
		event.key.keysym.sym == SDLK_a ? move(1) : 0;
		event.key.keysym.sym == SDLK_s ? move(2) : 0;
		event.key.keysym.sym == SDLK_d ? move(3) : 0;
	}
	else if (event.type == SDL_MOUSEMOTION)
		wolf->angle -= (double)(event.motion.xrel) / 15;
	render(wolf);
}

void			run(t_wolf *wolf)
{
	SDL_Event	ev;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		write(2, "wolf3d: SDL failed to init\n", 27);
	else if ((wolf->win = SDL_CreateWindow("Wolf3d", 0, 0, WINX, WINY,
	SDL_WINDOW_SHOWN)) && (wolf->ren = SDL_CreateRenderer(wolf->win, -1,
	SDL_RENDERER_ACCELERATED)))
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		while ((wolf->running))
			while (SDL_PollEvent(&ev))
				event(ev, wolf);
		SDL_DestroyWindow(wolf->win);
	}
	else
		write(2, "wolf3d: SDL failed to create window\n", 36);
	SDL_Quit();
}

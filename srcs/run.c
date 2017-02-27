/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:09:57 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 16:10:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <unistd.h>
#include <time.h>

static void		move(int dir, t_wolf *wolf, int shift)
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
	mx *= shift ? SPRINT * SPEED : SPEED;
	my *= shift ? SPRINT * SPEED : SPEED;
	if (wolf->posx + mx > 0 && wolf->posx + mx < wolf->line &&
	wolf->map[(int)(floor(wolf->posx + mx) + floor(wolf->posy)
	* wolf->line)] == FLOOR)
		wolf->posx += mx;
	if (wolf->posy + my > 0 && wolf->posy + my < wolf->size / wolf->line &&
	wolf->map[(int)(floor(wolf->posx) + floor(wolf->posy + my)
	* wolf->line)] == FLOOR)
		wolf->posy += my;
}

static void		event(SDL_Event event, t_wolf *wolf)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		wolf->angle -= (double)(event.motion.xrel) / 15;
		wolf->pitch -= (double)(event.motion.yrel);
	}
	else if (event.type == SDL_WINDOWEVENT && event.window.event ==
	SDL_WINDOWEVENT_CLOSE)
		wolf->status = 0;
	wolf->pitch > WINX ? wolf->pitch = WINX : 0;
	wolf->pitch < -WINX ? wolf->pitch = -WINX : 0;
}

static void		update(t_wolf *wolf)
{
	const Uint8		*status;

	status = SDL_GetKeyboardState(NULL);
	status[SDL_SCANCODE_ESCAPE] ? wolf->status = 0 : 0;
	status[SDL_SCANCODE_W] ? move(0, wolf, status[SDL_SCANCODE_LSHIFT]) : 0;
	status[SDL_SCANCODE_A] ? move(1, wolf, status[SDL_SCANCODE_LSHIFT]) : 0;
	status[SDL_SCANCODE_S] ? move(2, wolf, status[SDL_SCANCODE_LSHIFT]) : 0;
	status[SDL_SCANCODE_D] ? move(3, wolf, status[SDL_SCANCODE_LSHIFT]) : 0;
}

void			run(t_wolf *wolf)
{
	SDL_Event	ev;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		error(0);
	else if ((wolf->win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN)) &&
	(wolf->ren = SDL_CreateRenderer(wolf->win, -1, SDL_RENDERER_ACCELERATED |
	SDL_RENDERER_PRESENTVSYNC)) && load_textures(wolf))
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		while ((wolf->status))
		{
			update(wolf);
			while (SDL_PollEvent(&ev))
				event(ev, wolf);
			render(wolf);
		}
		SDL_DestroyWindow(wolf->win);
	}
	else
		error(0);
	SDL_Quit();
}

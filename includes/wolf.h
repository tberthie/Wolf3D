/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:06:02 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/08 00:59:56 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WINX	(double)1920
# define WINY	(double)1080
# define FOV	(double)60

# define FLOOR	'.'
# define WALL	'0'
# define PLAYER	'x'

# include <SDL.h>

typedef struct	s_wolf
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	char			status;

	double			angle;
	double			pitch;
	double			posx;
	double			posy;
	double			dste;

	char			*map;
	int				line;
	int				size;

	int				pos[2];
	double			ratio[2];
}				t_wolf;

void			setup(int fd, t_wolf *wolf);
void			run(t_wolf *wolf);
void			render(t_wolf *wolf);
void			menu(t_wolf *wolf);
void			walls(int x, t_wolf *wolf, double vx, double vy);

double			rad(double angle);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:06:02 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/07 19:23:25 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WINX	(double)1000
# define WINY	(double)1000

# define CAM	(double)0.5
# define FOV	(double)60

# define FLOOR	'.'
# define WALL	'0'
# define DOOR	'-'
# define PLAYER	'x'

# include <SDL.h>

typedef struct	s_wolf
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	char			running;

	double			angle;
	double			posx;
	double			posy;
	double			dste;

	char			*map;
	int				line;
	int				size;
}				t_wolf;

void			setup(int fd, t_wolf *wolf);
void			run(t_wolf *wolf);
void			render(t_wolf *wolf);

double			rad(double angle);

#endif

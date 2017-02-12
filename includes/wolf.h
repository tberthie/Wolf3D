/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:06:02 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/12 17:10:12 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WINX	(double)1500
# define WINY	(double)1000
# define FOV	(double)60

# define FLOOR	'.'
# define PLAYER	'x'
# define BMP	64

# define FR		100
# define FG		100
# define FB		100

# include <SDL.h>

typedef struct	s_tx
{
	char			id;
	SDL_Texture		*tx;
}				t_tx;

typedef struct	s_wolf
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	char			status;

	double			angle;
	double			pitch;
	double			vx;
	double			vy;

	double			posx;
	double			posy;
	double			dste;

	char			*map;
	int				line;
	int				size;

	int				pos[2];
	double			ratio[2];

	SDL_Texture		*tx;
	t_tx			**txs;
}				t_wolf;

void			setup(int fd, t_wolf *wolf);
void			run(t_wolf *wolf);
void			render(t_wolf *wolf);
void			menu(t_wolf *wolf);
void			walls(int x, t_wolf *wolf);
char			load_textures(t_wolf *wolf);
char			find_texture(t_wolf *wolf);

double			rad(double angle);

#endif

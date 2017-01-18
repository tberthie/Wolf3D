/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:06:02 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/18 15:18:11 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WINX	(double)1920
# define WINY	(double)1080

# define CAM	(double)0.5
# define FOV	(double)90

# define FLOOR	'.'
# define WALL	'0'
# define PLAYER	'x'

typedef struct	s_wolf
{
	void	*mlx;
	void	*win;

	double	angle;
	double	posx;
	double	posy;
	double	dste;

	char	*map;
	int		line;
	int		size;

	int		bpp;
	int		ls;
	int		end;
}				t_wolf;

void			setup(int fd, t_wolf *wolf);
void			run(t_wolf *wolf);
void			render(t_wolf *wolf);

int				key(int code, t_wolf *wolf);

double			rad(double angle);

#endif

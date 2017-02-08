/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:56:46 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/08 01:10:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <math.h>

static int		insert(t_wolf *wolf, char **line)
{
	int		i;
	char	*newmap;

	newmap = ft_malloc(sizeof(char) * (wolf->size + ft_tablen(line) + 1));
	wolf->map ? ft_strcpy(newmap, wolf->map) : 0;
	i = 0;
	while (line[i])
	{
		if (ft_strlen(line[i]) != 1 ||
		(*(line[i]) == PLAYER && wolf->posx != -1))
			return (ft_errret("wolf3d", "map invalid", 0));
		if (*(line[i]) == PLAYER)
		{
			wolf->posx = i + 0.5;
			wolf->posy = wolf->size / wolf->line + 0.5;
		}
		newmap[wolf->size++] = *(line[i]) == PLAYER ? '.' : *(line[i]);
		free(line[i++]);
	}
	newmap[wolf->size] = 0;
	free(line);
	free(wolf->map);
	wolf->map = newmap;
	return (1);
}

static t_wolf	*init(t_wolf *wolf)
{
	wolf->status = 1;
	wolf->angle = 0;
	wolf->pitch = 0;
	wolf->map = 0;
	wolf->size = 0;
	wolf->line = 0;
	wolf->posx = -1;
	wolf->dste = WINX / 2 / tan(rad(FOV / 2));
	return (wolf);
}

void			setup(int fd, t_wolf *wolf)
{
	char	*line;
	char	**split;

	wolf = init(wolf);
	line = 0;
	while (ft_gnl(fd, &line))
	{
		if (!(split = ft_strsplit(line, ' ')))
			return ;
		!wolf->line ? wolf->line = ft_tablen(split) : 0;
		if (!ft_tablen(split) || (wolf->line && wolf->line != ft_tablen(split)))
			return ((void)ft_errret("wolf3d", "map invalid", 0));
		if (!insert(wolf, split))
			return ;
		free(line);
	}
	close(fd);
	if (wolf->posx == -1 || !wolf->size || !wolf->line)
		return ((void)ft_errret("wolf3d", "map invalid", 0));
	run(wolf);
}

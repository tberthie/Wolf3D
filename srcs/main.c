/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:19:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/07 18:18:27 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

#include <fcntl.h>

int			main(int ac, char **av)
{
	t_wolf		*wolf;
	int			fd;

	if (ac != 2)
		write(2, "usage: wolf3d [map]\n", 20);
	else if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		write(2, "wolf3d: ", 8);
		perror(av[1]);
	}
	else
	{
		wolf = ft_malloc(sizeof(t_wolf));
		setup(fd, wolf);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:44:21 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/12 18:26:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

#include <unistd.h>
#include <math.h>

double			rad(double angle)
{
	return (angle * M_PI / 180);
}

int				error(int ret)
{
	write(2, "wolf3d: ", 8);
	write(2, SDL_GetError(), ft_strlen(SDL_GetError()));
	write(2, "\n", 1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:23:47 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/16 12:36:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

void		*ft_malloc(int size)
{
	void	*p;

	if (!(p = malloc(size)))
	{
		write(2, "\x1b[31merror\x1b[0m: malloc failed for ", 35);
		ft_putnbr_fd(size, 2);
		write(2, " bits\n", 6);
		exit(-1);
	}
	return (p);
}

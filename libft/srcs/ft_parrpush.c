/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:36:34 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/08 14:10:49 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	ft_parrpush(void ***tab, void *elem)
{
	void			**n_tab;
	unsigned int	arr_len;

	arr_len = 0;
	while ((*tab)[arr_len])
		arr_len++;
	n_tab = (void**)ft_malloc(sizeof(void*) * (arr_len + 2));
	n_tab[arr_len] = elem;
	n_tab[arr_len + 1] = (void*)0;
	if (n_tab == *tab)
		return ;
	while (arr_len--)
		n_tab[arr_len] = (*tab)[arr_len];
	free(*tab);
	*tab = n_tab;
}

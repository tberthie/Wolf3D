/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:21:52 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/26 01:28:25 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

static char		add_texture(t_wolf *wolf, char id, char *path)
{
	SDL_Surface		*sf;
	t_tx			*tx;

	if (!(sf = SDL_LoadBMP(path)))
		return (0);
	tx = ft_malloc(sizeof(t_tx));
	tx->id = id;
	tx->tx = sf;
	ft_parrpush((void***)&wolf->txs, tx);
	return (1);
}

char			load_textures(t_wolf *wolf)
{
	wolf->txs = ft_malloc(sizeof(t_tx*));
	*wolf->txs = 0;
	if (!add_texture(wolf, '0', "Textures/wall_black.bmp")
	|| !add_texture(wolf, '1', "Textures/wall_white.bmp"))
		return (0);
	return (1);
}

char			find_texture(t_wolf *wolf)
{
	char	id;
	int		pos;

	pos = 0;
	id = wolf->map[*wolf->pos];
	while (wolf->txs[pos])
	{
		if (wolf->txs[pos]->id == id)
		{
			wolf->tx = wolf->txs[pos]->tx;
			return (1);
		}
		pos++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:21:52 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/12 17:13:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

static char		add_texture(t_wolf *wolf, char id, char *path)
{
	SDL_Surface		*sf;
	t_tx			*tx;

	if (!(sf = SDL_LoadBMP(path)))
	{
		write(2, "wolf3d: file not found: ", 24);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (0);
	}
	tx = ft_malloc(sizeof(t_tx));
	tx->id = id;
	tx->tx = SDL_CreateTextureFromSurface(wolf->ren, sf);
	SDL_FreeSurface(sf);
	ft_parrpush((void***)&wolf->txs, tx);
	return (1);
}

char			load_textures(t_wolf *wolf)
{
	wolf->txs = ft_malloc(sizeof(t_tx*));
	*wolf->txs = 0;
	if (!add_texture(wolf, '0', "Textures/Black.bmp"))
		return (0);
	return (1);
}

char		find_texture(t_wolf *wolf)
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

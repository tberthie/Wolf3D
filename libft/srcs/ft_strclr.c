/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:10:36 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/09 12:37:17 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_strclr(char *s)
{
	if (s)
		while (*s)
			*s++ = '\0';
}

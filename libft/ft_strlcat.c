/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:05:04 by femullao          #+#    #+#             */
/*   Updated: 2024/10/08 17:05:02 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ds;
	size_t	sr;
	size_t	i;

	ds = ft_strlen(dst);
	sr = ft_strlen(src);
	i = 0;
	if (dstsize <= ds)
		return (sr + dstsize);
	while (src[i] && ds + i + 1 < dstsize)
	{
		dst[ds + i] = src[i];
		i++;
	}
	dst[ds + i] = '\0';
	return (ds + sr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:50:28 by femullao          #+#    #+#             */
/*   Updated: 2024/10/12 12:47:21 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*b;
	size_t	i;

	b = (char *)s;
	i = 0;
	while (i < n)
	{
		if (b[i] == (char)c)
			return (b + i);
		i++;
	}
	return (NULL);
}

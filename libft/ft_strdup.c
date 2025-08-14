/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:12:54 by femullao          #+#    #+#             */
/*   Updated: 2024/10/12 17:18:08 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*b;
	size_t	i;

	b = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!b)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}

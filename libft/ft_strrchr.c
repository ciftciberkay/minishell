/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:38:08 by femullao          #+#    #+#             */
/*   Updated: 2024/10/12 17:30:00 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	ct;

	ct = ft_strlen(s);
	while (ct >= 0)
	{
		if (s[ct] == (char)c)
			return ((char *)s + ct);
		ct--;
	}
	return (NULL);
}

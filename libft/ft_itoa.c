/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:39:59 by femullao          #+#    #+#             */
/*   Updated: 2024/10/15 17:26:27 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenofint(int a)
{
	int	ct;

	ct = 0;
	if (a <= 0)
	{
		ct++;
		a = -a;
	}
	while (a > 0)
	{
		a /= 10;
		ct++;
	}
	return (ct);
}

char	*ft_itoa(int n)
{
	int		length;
	int		sign;
	char	*res;

	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = lenofint(n);
	res = malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	res[length] = '\0';
	while (length-- > 0)
	{
		res[length] = (n % 10) + 48;
		n /= 10;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

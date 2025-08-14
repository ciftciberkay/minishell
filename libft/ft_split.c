/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:16:52 by femullao          #+#    #+#             */
/*   Updated: 2024/10/17 16:00:32 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordct(char const *s, char sep)
{
	int	i;
	int	ct;

	ct = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i])
			ct++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (ct);
}

static char	*ft_alloction(char const *str, int i, int j)
{
	char	*res;

	res = malloc(sizeof(char) * (i - j + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &str[j], i - j + 1);
	return (res);
}

static char	**ft_free(char **res, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	int		i;
	int		j;
	int		k;

	k = 0;
	r = malloc(sizeof(char *) * (wordct(s, c) + 1));
	i = 0;
	if (!s || !r)
		return (NULL);
	while (s[i] && k < wordct(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			r[k++] = ft_alloction(s, i, j);
		if (r[k - 1] == NULL)
			return (ft_free(r, k));
	}
	r[k] = NULL;
	return (r);
}

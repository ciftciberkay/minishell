/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:39:30 by macbook6          #+#    #+#             */
/*   Updated: 2025/07/19 14:32:00 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_redirect_char(char c)
{
	return (c == '<' || c == '>');
}

int	is_append(char *ret, int i)
{
	ret[i] = APPEND;
	ret[i + 1] = APPEND;
	i++;
	return (i);
}

int	is_heredoc(char *ret, int i)
{
	ret[i] = HEREDOC;
	ret[i + 1] = HEREDOC;
	i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

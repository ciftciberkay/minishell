/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:13:03 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:13:04 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_join(const char *str, size_t start, size_t end)
{
	char	*sbstr;
	char	*ret;

	sbstr = ft_substr(str, start, end);
	ret = ft_strjoin(sbstr, "=");
	free(sbstr);
	return (ret);
}

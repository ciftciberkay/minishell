/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_menv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:09:48 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:09:51 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_menv(char **env)
{
	char	**menv;
	int		i;

	i = 0;
	while (env[i])
		i++;
	menv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		menv[i] = ft_strdup(env[i]);
		i++;
	}
	menv[i] = NULL;
	return (menv);
}

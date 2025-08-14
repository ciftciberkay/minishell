/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_menv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:04:52 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 19:04:55 by macbook6         ###   ########.fr       */
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

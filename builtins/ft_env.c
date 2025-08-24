/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:23:39 by femullao          #+#    #+#             */
/*   Updated: 2025/08/16 20:36:41 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_env(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(arg, env[i], ft_strlen(arg)))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_value(char *line)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=')
		return (&line[i + 1]);
	return (NULL);
}

char	*get_key(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(line);
	if (!tmp)
	{
		ft_putendl_fd("tmpisnull at getkey", 1);
		return (NULL);
	}
	while (tmp[i] != '=')
		i++;
	i++;
	tmp[i] = '\0';
	return (tmp);
}

t_mini	*update_env(char *key, char *newdata, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->menv[i])
	{
		if (!ft_strncmp(key, mini->menv[i], ft_strlen(key)))
		{
			free(mini->menv[i]);
			mini->menv[i] = ft_strjoin(key, newdata);
			if (!mini->menv[i])
				exit(EXIT_FAILURE);
			return (mini);
		}
		i++;
	}
	return (mini);
}

void	ft_env(char **env, t_mini *mini)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	mini->exitcode = 0;
}

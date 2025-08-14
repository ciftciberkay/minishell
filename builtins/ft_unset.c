/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:00:48 by femullao          #+#    #+#             */
/*   Updated: 2025/08/03 14:19:31 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_lines(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	unset_from_env(t_mini *mini, char *arg)
{
	char	**new_env;
	char	*key;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (count_lines(mini->menv) + 1));
	if (!new_env)
		return ;
	while (mini->menv[i])
	{
		key = get_key(mini->menv[i]);
		if (ft_strncmp(key, arg, ft_strlen(arg))
			|| (ft_strlen(key) - 1 != ft_strlen(arg)))
			new_env[j++] = ft_strdup(mini->menv[i]);
		free (key);
		i++;
	}
	new_env[j] = NULL;
	free_pp(mini->menv);
	mini->menv = new_env;
}

void	ft_unset(t_mini *mini, char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		unset_from_env(mini, arg[i]);
		i++;
	}
	mini->exitcode = 0;
}

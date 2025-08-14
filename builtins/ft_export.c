/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:30:14 by femullao          #+#    #+#             */
/*   Updated: 2025/08/09 18:05:33 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_update_env(char *value, char *env_value)
{
	size_t	val_len;
	size_t	env_len;

	val_len = ft_strlen(value);
	env_len = ft_strlen(env_value);
	return (ft_strncmp(value, env_value, env_len) != 0 || val_len != env_len);
}

static void	handle_env_update(t_mini *mini, char *arg, char *key, char *value)
{
	char	*env_entry;

	env_entry = get_from_env(mini->menv, key);
	if (env_entry)
	{
		if (should_update_env(value, get_value(env_entry)))
			mini = update_env(key, value, mini);
	}
	else
		add_env(mini, arg);
}

void	check_valid_arg(char **args, t_mini *mini)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (args[i])
	{
		if (ft_isdigit(args[i][0]) || args[i][0] == '=' || check_chars(args[i]))
			print_error_export(mini);
		else if (ft_strchr(args[i], '=') != NULL)
		{
			key = get_key(args[i]);
			value = get_value(args[i]);
			handle_env_update(mini, args[i], key, value);
			free(key);
		}
		i++;
	}
}

void	ft_export(t_mini *mini, char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		while (mini->menv[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(mini->menv[i], STDOUT_FILENO);
			i++;
		}
		return ;
	}
	mini->exitcode = 0;
	check_valid_arg(args + 1, mini);
}

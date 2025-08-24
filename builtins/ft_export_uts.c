/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_uts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:06:42 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 16:58:31 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_export(t_mini *mini)
{
	ft_putstr_fd("aoshell: export: ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	mini->exitcode = 1;
}

char	**ft_strlcpy_n_replace(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
	{
		dst[i] = src[i];
		i++;
	}
	free(src);
	return (dst);
}

void	add_env(t_mini *mini, char *arg)
{
	int		i;
	char	**new_menv;

	i = 0;
	while (mini->menv[i] != NULL)
		i++;
	new_menv = ft_calloc(i + 2, sizeof(char *));
	if (new_menv == NULL)
		exit(EXIT_FAILURE);
	mini->menv = ft_strlcpy_n_replace(new_menv, mini->menv);
	mini->menv[i] = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (mini->menv[i] == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(mini->menv[i], arg, ft_strlen(arg) + 1);
	mini->menv[i + 1] = NULL;
}

int	check_chars(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

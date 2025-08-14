/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:53:34 by femullao          #+#    #+#             */
/*   Updated: 2025/07/20 17:51:53 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	newline_control(char *arg)
{
	int	i;

	i = 1;
	if (arg == NULL)
		return (0);
	if (ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **args, t_mini *mini)
{
	int	check_n;
	int	i;

	check_n = 0;
	i = 0;
	while (args[i])
	{
		if (newline_control(args[i]))
		{
			check_n = 1;
			i++;
		}
		else
			break ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!check_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	mini->exitcode = 0;
}

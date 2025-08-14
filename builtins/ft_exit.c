/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:01:20 by femullao          #+#    #+#             */
/*   Updated: 2025/08/02 13:58:56 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nonnum_exit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return (1);
	if (arg[i] == '+' || arg[i] == '-' )
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_exit_nonnum(t_mini *mini)
{
	free_parser(mini);
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putendl_fd(" numeric argument required", STDERR_FILENO);
	exit (2);
}

static void	ft_exit_tma(t_mini *mini)
{
	free_parser(mini);
	ft_putendl_fd(" too many arguments", STDERR_FILENO);
	exit (1);
}

static void	ft_exit_num(t_mini *mini, int code)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_parser(mini);
	exit(code);
}

void	ft_exit(char **arg, t_mini *mini)
{
	int	code;

	if (arg[1])
		code = ft_atoi(arg[1]);
	if (arg[1] == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		free_parser(mini);
		exit(mini->exitcode);
	}
	else if (nonnum_exit(arg[1]))
		ft_exit_nonnum(mini);
	else if (arg[2])
		ft_exit_tma(mini);
	else
		ft_exit_num(mini, code);
}

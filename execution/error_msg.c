/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:52:17 by femullao          #+#    #+#             */
/*   Updated: 2025/08/09 16:35:32 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmd_error(char *cmd, int flag, t_mini *mini)
{
	if (flag == 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (flag == 1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if (flag == 2)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if (flag == 3)
		ft_putendl_fd(" Is a directory", STDERR_FILENO);
	free_parser(mini);
	free_pp(mini->menv);
	exit(127 - (flag % 2));
}

void	ft_cmd_file_error(char *cmd, int flag, int exitflag, t_mini *mini)
{
	if (flag == 1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	if (flag == 2)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	if (flag == 3)
		ft_putendl_fd(" Is a directory: ", STDERR_FILENO);
	if (exitflag)
		exit(1);
	else
	{
		mini->exitcontrol = -1;
		mini->exitcode = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:05:49 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 19:07:55 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(char **args, t_mini *mini)
{
	char	*cmdpth;

	if (ft_strchr(args[0], '/'))
	{
		cmdpth = args[0];
		check_pth(cmdpth, mini);
	}
	else
		cmdpth = find_cmd_path(args, mini);
	execve(cmdpth, args, mini->menv);
}

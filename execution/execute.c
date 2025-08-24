/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:10:10 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 18:06:53 by femullao         ###   ########.fr       */
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
	if (!cmdpth)
		return ;
	execve(cmdpth, args, mini->menv);
}

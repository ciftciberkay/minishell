/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:52:00 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:09:39 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_command_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, ".", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "..", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	execute_builtin(char **args, t_mini *mini)
{
	if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(args, mini);
	else if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(args + 1, mini);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ft_pwd(mini);
	else if (!ft_strncmp(args[0], "export", 7))
		ft_export(mini, args);
	else if (!ft_strncmp(args[0], "unset", 6))
		ft_unset(mini, args);
	else if (!ft_strncmp(args[0], "env", 4))
		ft_env(mini->menv, mini);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(args++, mini);
}

void	only_one_builtin(t_command *cmd, t_mini *mini)
{
	cmd->the_flag = 0;
	if (apply_redirects(cmd, mini))
		return ;
	if (mini->exitcontrol == -1)
		return ;
	execute_builtin(cmd->argv, mini);
}

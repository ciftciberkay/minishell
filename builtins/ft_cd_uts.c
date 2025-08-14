/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_uts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:03:08 by femullao          #+#    #+#             */
/*   Updated: 2025/08/09 18:03:10 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_pwd(t_mini *mini, char *new_pwd, char *old_pwd)
{
	mini = update_env("PWD=", new_pwd, mini);
	mini = update_env("OLDPWD=", old_pwd, mini);
}

void	ft_puterror_cd(char *ptr, char *to_free)
{
	free(to_free);
	ft_putstr_fd("cd: ", STDOUT_FILENO);
	ft_putstr_fd(ptr, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

int	arg_counter(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	handle_too_many_args(t_mini *mini)
{
	ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
	mini->exitcode = 1;
}

void	handle_cd_error(char *pwd, t_mini *mini, char *arg)
{
	ft_puterror_cd(arg, pwd);
	mini->exitcode = 1;
}

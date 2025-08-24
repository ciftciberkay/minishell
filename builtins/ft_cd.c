/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:34:11 by femullao          #+#    #+#             */
/*   Updated: 2025/08/03 15:35:25 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cd(char *pwd, char *new_pwd)
{
	free(pwd);
	free(new_pwd);
}

void	cd_home(t_mini *mini, char *oldpwd)
{
	char	*home_path;
	char	*new_pwd;

	home_path = get_from_env(mini->menv, "HOME=");
	mini->exitcode = 1;
	if (!home_path)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		free(oldpwd);
		return ;
	}
	if (ft_strchr(home_path, '/') == NULL)
	{
		ft_puterror_cd(ft_strchr(home_path, '=') + 1, oldpwd);
		return ;
	}
	if (chdir(ft_strchr(home_path, '/')))
	{
		ft_puterror_cd(ft_strchr(home_path, '/'), oldpwd);
		return ;
	}
	mini->exitcode = 0;
	new_pwd = getcwd(NULL, 0);
	update_env_pwd(mini, new_pwd, oldpwd);
	free_cd(oldpwd, new_pwd);
}

void	ft_cd(char **arg, t_mini *mini)
{
	char	*pwd;
	char	*new_pwd;

	if (arg_counter(arg) > 2)
		handle_too_many_args(mini);
	else
	{
		pwd = getcwd(NULL, 0);
		if (!arg[1])
		{
			cd_home(mini, pwd);
			return ;
		}
		else if (chdir(arg[1]))
		{
			handle_cd_error(pwd, mini, arg[1]);
			return ;
		}
		new_pwd = getcwd(NULL, 0);
		update_env_pwd(mini, new_pwd, pwd);
		free(new_pwd);
		free(pwd);
		mini->exitcode = 0;
	}
}

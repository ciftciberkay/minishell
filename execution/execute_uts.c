/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_uts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:06:33 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 19:08:16 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_paths(char **env)
{
	while (*env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
			return (*env);
		env++;
	}
	return (NULL);
}

static char	*try_path_for_cmd(char *base_path, char *cmd, t_mini *mini)
{
	char	*tmp;
	char	*test;

	tmp = ft_strjoin(base_path, "/");
	test = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(test, F_OK) == 0)
	{
		if (access(test, X_OK) == 0)
			return (test);
		else
		{
			free(test);
			ft_cmd_error(cmd, 1, mini);
		}
	}
	free(test);
	return (NULL);
}

char	*get_cmd_from_paths(char *cmd, char **psb_paths, t_mini *mini)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (psb_paths[i])
	{
		result = try_path_for_cmd(psb_paths[i], cmd, mini);
		if (result)
			break ;
		i++;
	}
	return (result);
}

char	*find_cmd_path(char **args, t_mini *mini)
{
	char	*envpth;
	char	**psb_paths;
	char	*cmd;
	char	*result;

	result = NULL;
	envpth = get_env_paths(mini->menv);
	cmd = args[0];
	psb_paths = ft_split(ft_strchr(envpth, '/'), ':');
	result = get_cmd_from_paths(cmd, psb_paths, mini);
	free_pp(psb_paths);
	if (!result)
		ft_cmd_error(cmd, 0, mini);
	return (result);
}

void	check_pth(char *path, t_mini *mini)
{
	if (is_directory(path))
		ft_cmd_error(path, 3, mini);
	if (access(path, X_OK) == 0)
		return ;
	else if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
		ft_cmd_error(path, 1, mini);
	else if (access(path, F_OK) == -1)
		ft_cmd_error(path, 2, mini);
}

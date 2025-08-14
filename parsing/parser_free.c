/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:31:15 by beciftci          #+#    #+#             */
/*   Updated: 2025/07/27 15:14:54 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_redirects(t_redirects *redir_list)
{
	t_redirects	*temp;

	while (redir_list)
	{
		temp = redir_list->next;
		free(redir_list->name);
		free(redir_list);
		redir_list = temp;
	}
}

void	free_commands(t_command *cmd_list)
{
	t_command	*temp_cmd;

	while (cmd_list)
	{
		temp_cmd = cmd_list->next;
		free_split(cmd_list->argv);
		free_redirects(cmd_list->ret);
		free(cmd_list);
		cmd_list = temp_cmd;
	}
}

void	free_parser(t_mini *mini)
{
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->tokenized)
	{
		free(mini->tokenized);
		mini->tokenized = NULL;
	}
	if (mini->sub_pipes)
	{
		free_split(mini->sub_pipes);
		mini->sub_pipes = NULL;
	}
	if (mini->pipe_locs)
	{
		free(mini->pipe_locs);
		mini->pipe_locs = NULL;
	}
	if (mini->cmd)
	{
		free_commands(mini->cmd);
		mini->cmd = NULL;
	}
}

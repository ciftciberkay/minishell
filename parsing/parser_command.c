/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:55:52 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 20:31:33 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_quoted_string(char *str, int *i, char quote_char)
{
	quote_char = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (str[*i] == quote_char)
		(*i)++;
	return (1);
}

int	process_unquoted_string(char *str, int *i)
{
	while (str[*i] && !ft_isspace(str[*i]) && !is_redirect_char(str[*i])
		&& str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	return (1);
}

static int	process_single_command(t_mini *mini, t_command *current_cmd, int i)
{
	current_cmd->argv = extract_argv(mini->sub_pipes[i]);
	current_cmd->ret = extract_redirects(mini->sub_pipes[i]);
	if (!current_cmd->argv && !current_cmd->ret
		&& mini->sub_pipes[i] && ft_strlen(mini->sub_pipes[i]) > 0)
	{
		free_commands(mini->cmd);
		mini->cmd = NULL;
		free(current_cmd);
		return (0);
	}
	return (1);
}

static int	create_and_process_command(t_mini *mini, int i)
{
	t_command	*current_cmd;

	current_cmd = create_command_node();
	if (!current_cmd)
	{
		free_commands(mini->cmd);
		mini->cmd = NULL;
		return (0);
	}
	if (!process_single_command(mini, current_cmd, i))
		return (0);
	add_command_to_list(&(mini->cmd), current_cmd);
	return (1);
}

void	parse_commands(t_mini *mini)
{
	int	i;

	mini->cmd = NULL;
	i = 0;
	if (!mini->sub_pipes)
		return ;
	while (mini->sub_pipes[i])
	{
		if (!create_and_process_command(mini, i))
			return ;
		i++;
	}
}

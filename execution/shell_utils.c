/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beciftci <beciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:44:12 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/14 16:44:13 by beciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_input(t_mini *mini)
{
	if (check_syntax_errors(mini->input) || !mini->input[0]
		|| quote_check(mini->input))
	{
		free(mini->input);
		return (0);
	}
	return (1);
}

int	process_dollar(t_mini *mini)
{
	char	*processed_input;

	processed_input = process_dollar_signs(mini->input, mini->menv, mini);
	if (!processed_input || !processed_input[0])
	{
		free(mini->input);
		if (processed_input)
			free(processed_input);
		return (0);
	}
	free(mini->input);
	mini->input = processed_input;
	return (1);
}

void	execute_command_line(t_mini *mini)
{
	parse(mini);
	execute(mini->cmd, mini);
	free_parser(mini);
	free(mini->input);
}

void	shell_loop(t_mini *mini)
{
	while (1)
	{
		mini->exitcontrol = 1;
		mini->input = readline("aoshell> ");
		if (!mini->input)
			break ;
		if (!process_input(mini))
			continue ;
		add_history(mini->input);
		if (!process_dollar(mini))
			continue ;
		execute_command_line(mini);
	}
	free_pp(mini->menv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:44:12 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/17 16:38:20 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_input(t_mini *mini)
{
	if (check_syntax_errors(mini->input)
		|| quote_check(mini->input))
	{
		free(mini->input);
		mini->exitcode = 2;
		return (0);
	}
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
	char	*tmp;

	while (1)
	{
		mini->exitcontrol = 1;
		tmp = readline("aoshell> ");
		if (!tmp)
			break ;
		mini->input = ft_strtrim(tmp, " \t\n\f\r\v");
		free(tmp);
		if (!mini->input)
			break ;
		add_history(mini->input);
		if (!process_input(mini))
			continue ;
		execute_command_line(mini);
	}
	free_pp(mini->menv);
}

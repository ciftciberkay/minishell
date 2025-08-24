/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:12:23 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:12:26 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tokenizer(char *input)
{
	char	*ret;

	ret = ft_strdup(input);
	mark_each(input, ret, 0);
	quotes_in(ret);
	return (ret);
}

void	determine_pipe_locs_and_split(t_mini *mini)
{
	int	i;
	int	pipe_c;

	pipe_c = 0;
	i = 0;
	while (mini->tokenized[i])
	{
		if (mini->tokenized[i] == PIPE)
			pipe_c++;
		i++;
	}
	if (!allocate_pipe_arrays(mini, pipe_c))
		return ;
	find_pipe_locations(mini);
	get_sub_pipes(mini, pipe_c, 0);
}

void	parse(t_mini *mini)
{
	mini->tokenized = tokenizer(mini->input);
	if (!mini->tokenized)
		return ;
	determine_pipe_locs_and_split(mini);
	if (!mini->sub_pipes)
	{
		free(mini->tokenized);
		mini->tokenized = NULL;
		return ;
	}
	parse_commands(mini);
}

void	quotes_in(char *tokenized)
{
	int	i;

	i = 0;
	while (tokenized[i])
	{
		if (tokenized[i] == DQUOTE)
		{
			i++;
			while (tokenized[i] != DQUOTE && tokenized[i])
			{
				tokenized[i] = CHAR;
				i++;
			}
		}
		else if (tokenized[i] == SQUOTE)
		{
			while (tokenized[++i] != SQUOTE)
				tokenized[i] = CHAR;
		}
		i++;
	}
}

int	quote_check(char *input)
{
	int	db_count;
	int	sg_count;
	int	i;

	db_count = 0;
	sg_count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && db_count % 2 == 0
			&& (i == 0 || input[i - 1] != '\\'))
			sg_count++;
		else if (input[i] == '"' && sg_count % 2 == 0
			&& (i == 0 || input[i - 1] != '\\'))
			db_count++;
		i++;
	}
	if (!(db_count % 2 == 0) || !(sg_count % 2 == 0))
	{
		ft_putstr_fd("quote error\n", 2);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_locs_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:00:14 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 21:03:59 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allocate_pipe_arrays(t_mini *mini, int pipe_c)
{
	mini->sub_pipes = malloc(sizeof(char *) * (pipe_c + 2));
	if (!mini->sub_pipes)
		return (0);
	ft_memset(mini->sub_pipes, 0, sizeof(char *) * (pipe_c + 2));
	if (pipe_c > 0)
	{
		mini->pipe_locs = malloc(sizeof(int) * (pipe_c + 1));
		if (!mini->pipe_locs)
		{
			free(mini->sub_pipes);
			mini->sub_pipes = NULL;
			return (0);
		}
		ft_memset(mini->pipe_locs, 0, (pipe_c + 1) * sizeof(int));
	}
	else
		mini->pipe_locs = NULL;
	return (1);
}

void	find_pipe_locations(t_mini *mini)
{
	int	i;
	int	pipe_index;

	i = 0;
	pipe_index = 0;
	while (mini->tokenized[i])
	{
		if (mini->tokenized[i] == PIPE)
			mini->pipe_locs[pipe_index++] = i;
		i++;
	}
}

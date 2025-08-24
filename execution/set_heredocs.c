/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:10:39 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:10:41 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_loop(t_redirects *tmp, int hfd[2])
{
	char	*inp;

	while (1)
	{
		inp = readline("> ");
		if (!inp)
			break ;
		else if (ft_strncmp(inp, tmp->name, ft_strlen(tmp->name) + 1) == 0)
		{
			free(inp);
			break ;
		}
		ft_putendl_fd(inp, hfd[1]);
		free(inp);
	}
	close(hfd[1]);
}

void	prepare_heredocs(t_command *cmd)
{
	t_command	*curr;
	t_redirects	*tmp;
	int			hfd[2];

	curr = cmd;
	while (curr)
	{
		tmp = curr->ret;
		while (tmp)
		{
			tmp->heredoc_fd = -1;
			if (tmp->type == HEREDOC)
			{
				pipe(hfd);
				heredoc_loop(tmp, hfd);
				tmp->heredoc_fd = hfd[0];
			}
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}

int	is_stdinrdr(t_command *cmd)
{
	t_redirects	*tmp;

	tmp = cmd->ret;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

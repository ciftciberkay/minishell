/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:39:53 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 19:41:38 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		return (0);
	}
	return (S_ISDIR(statbuf.st_mode));
}

void	backup_fds(int backup[2], int *in_fd)
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	*in_fd = STDIN_FILENO;
}

void	restore_fds(int backup[2])
{
	dup2(backup[0], STDIN_FILENO);
	close(backup[0]);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[1]);
}

void	execute(t_command *cmd, t_mini *mini)
{
	t_command	*curr;
	int			pipe_fd[2];
	int			backup[2];
	int			in_fd;

	backup_fds(backup, &in_fd);
	prepare_heredocs(cmd);
	curr = cmd;
	while (curr)
	{
		if (curr->next)
			pipe(pipe_fd);
		if (cmd == curr && is_command_builtin(curr->argv[0]) && !curr->next)
		{
			if (cmd->ret)
				cmd->ret->exitflag = 0;
			only_one_builtin(curr, mini);
		}
		else
			child_process(curr, pipe_fd, in_fd, mini);
		set_stdin(&in_fd, pipe_fd, curr);
		curr = curr->next;
	}
	waiting_children(cmd, mini, cmd->the_flag);
	restore_fds(backup);
}

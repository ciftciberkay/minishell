/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:44:03 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/16 20:12:58 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_mini *mini)
{
	free_parser(mini);
	free_pp(mini->menv);
}

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	chd_proc(t_command *cmd, int pipe_fd[2], int in_fd, t_mini *mini)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (!is_stdinrdr(cmd) && in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (cmd->next)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close_pipe(pipe_fd);
		}
		if (apply_redirects(cmd, mini))
			exit(mini->exitcode);
		if (cmd && cmd->argv && cmd->argv[0])
		{
			if (is_command_builtin(cmd->argv[0]))
				execute_builtin(cmd->argv, mini);
			else
				execute_command(cmd->argv, mini);
		}
		free_all(mini);
		exit(mini->exitcode);
	}
}

void	waiting_children(t_command *cmd, t_mini *mini, int the_flag)
{
	int			status;
	t_command	*curr;

	curr = cmd;
	while (curr)
	{
		status = 0;
		waitpid(curr->pid, &status, 0);
		if (the_flag)
		{
			if (WIFEXITED(status))
				mini->exitcode = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exitcode = 128 + WTERMSIG(status);
		}
		curr = curr->next;
	}
}

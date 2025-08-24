/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:10:19 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:10:21 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_output_redirect(t_redirects *redirect, t_mini *mini)
{
	int	fd;

	fd = open(redirect->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
	{
		if (access(redirect->name, W_OK) == -1)
			return (ft_cmd_file_error(redirect->name, 1,
					redirect->exitflag, mini), 1);
		if (is_directory(redirect->name))
			return (ft_cmd_file_error(redirect->name, 3,
					redirect->exitflag, mini), 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_append_redirect(t_redirects *redirect, t_mini *mini)
{
	int	fd;

	fd = open(redirect->name, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fd == -1)
	{
		if (access(redirect->name, W_OK) == -1)
			return (ft_cmd_file_error(redirect->name, 1,
					redirect->exitflag, mini), 1);
		if (is_directory(redirect->name))
			return (ft_cmd_file_error(redirect->name, 3,
					redirect->exitflag, mini), 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_stdin_redirect(t_redirects *redirect, t_mini *mini, int fd)
{
	if (redirect->type == INPUT)
	{
		fd = open(redirect->name, O_RDONLY);
		if (fd == -1)
		{
			if (access(redirect->name, F_OK) == -1)
				return (ft_cmd_file_error(redirect->name, 2,
						redirect->exitflag, mini), 1);
			if (access(redirect->name, R_OK) == -1)
				return (ft_cmd_file_error(redirect->name, 1,
						redirect->exitflag, mini), 1);
			if (is_directory(redirect->name), 1)
				return (ft_cmd_file_error(redirect->name, 3,
						redirect->exitflag, mini), 1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redirect->type == HEREDOC && redirect->heredoc_fd != -1)
	{
		dup2(redirect->heredoc_fd, STDIN_FILENO);
		close(redirect->heredoc_fd);
	}
	return (0);
}

void	set_stdin(int *in_fd, int pipe_fd[2], t_command *curr)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (curr->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

int	apply_redirects(t_command *cmd, t_mini *mini)
{
	t_redirects	*tmp;
	int			status;

	status = 0;
	tmp = cmd->ret;
	while (tmp)
	{
		if (tmp->type == OUTPUT)
			status = handle_output_redirect(tmp, mini);
		else if (tmp->type == APPEND)
			status = handle_append_redirect(tmp, mini);
		else if (tmp->type == INPUT || tmp->type == HEREDOC)
			status = handle_stdin_redirect(tmp, mini, 0);
		if (status == 1)
			return (status);
		tmp = tmp->next;
	}
	return (status);
}

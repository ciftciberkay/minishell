/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:39:53 by femullao          #+#    #+#             */
/*   Updated: 2025/08/14 20:31:31 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int ptr)
{
	(void)ptr;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:31:03 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/09 21:15:11 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void) av;
	mini.exitcode = 0;
	signal_handler();
	mini.menv = create_menv(env);
	if (ac == 1)
	{
		shell_loop(&mini);
		return (mini.exitcode);
	}
	return (1);
}

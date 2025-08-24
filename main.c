/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:13:08 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:13:09 by femullao         ###   ########.fr       */
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

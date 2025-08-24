/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:24:09 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 19:24:12 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote_status(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (c == '\"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}

int	handle_input_redirect_type(char *str, int *i)
{
	if (str[*i + 1] == '<')
	{
		*i += 2;
		return (HEREDOC);
	}
	else
	{
		(*i)++;
		return (INPUT);
	}
}

int	handle_output_redirect_type(char *str, int *i)
{
	if (str[*i + 1] == '>')
	{
		*i += 2;
		return (APPEND);
	}
	else
	{
		(*i)++;
		return (OUTPUT);
	}
}

int	get_redirect_type(char *str, int *i)
{
	if (str[*i] == '<')
		return (handle_input_redirect_type(str, i));
	else if (str[*i] == '>')
		return (handle_output_redirect_type(str, i));
	return (0);
}

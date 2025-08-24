/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mssg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:11:36 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:11:37 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_initial_errors(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

static int	check_pipe_error(const char *input, int *i)
{
	(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

static int	check_redirect_error(const char *input, int *i)
{
	char	redirect_type;

	redirect_type = input[*i];
	(*i)++;
	if (input[*i] == redirect_type)
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || is_redirect_char(input[*i]) || input[*i] == '|')
	{
		printf("syntax error near unexpected token after `%c'\n",
			redirect_type);
		return (1);
	}
	return (0);
}

static int	proc_chr(const char *input, int *i, int *in_squote, int *in_dquote)
{
	if (input[*i] == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (input[*i] == '\"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
	else if (!(*in_squote) && !(*in_dquote))
	{
		if (input[*i] == '|' && check_pipe_error(input, i))
			return (1);
		else if (is_redirect_char(input[*i]) && check_redirect_error(input, i))
			return (1);
	}
	return (0);
}

int	check_syntax_errors(const char *input)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	if (check_initial_errors(input, &i))
		return (1);
	while (input[i])
	{
		if (proc_chr(input, &i, &in_squote, &in_dquote))
			return (1);
		if (input[i])
			i++;
	}
	return (0);
}

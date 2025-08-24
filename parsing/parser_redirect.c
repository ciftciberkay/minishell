/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:12:11 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:12:12 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_whitespace(char *str, int *idx)
{
	while (str[*idx] && ft_isspace(str[*idx]))
		(*idx)++;
	return (*idx);
}

static char	*extract_quoted_part(char *str, int *idx)
{
	char	quote_char;
	int		start;

	quote_char = str[*idx];
	(*idx)++;
	start = *idx;
	while (str[*idx] && str[*idx] != quote_char)
		(*idx)++;
	if (str[*idx] == quote_char)
		(*idx)++;
	return (ft_substr(str, start, *idx - start - 1));
}

static char	*extract_unquoted_part(char *str, int *idx)
{
	int		start;

	start = *idx;
	while (str[*idx] && !ft_isspace(str[*idx])
		&& !is_redirect_char(str[*idx]) && str[*idx] != '\''
		&& str[*idx] != '\"')
		(*idx)++;
	return (ft_substr(str, start, *idx - start));
}

static char	*extract_complete_filename(char *str, int *idx)
{
	char	*result;
	char	*temp_part;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*idx] && !ft_isspace(str[*idx]) && !is_redirect_char(str[*idx]))
	{
		if (str[*idx] == '\'' || str[*idx] == '\"')
			temp_part = extract_quoted_part(str, idx);
		else
			temp_part = extract_unquoted_part(str, idx);
		if (!temp_part)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, temp_part);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*get_redirect_name(t_mini *mini, char *str, int *idx)
{
	char	*name;
	char	*expanded;

	skip_whitespace(str, idx);
	name = extract_complete_filename(str, idx);
	if (!name)
		return (NULL);
	expanded = process_dollar_signs(name, mini);
	free(name);
	if (!expanded)
		return (NULL);
	return (expanded);
}

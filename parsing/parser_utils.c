/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:32:03 by beciftci          #+#    #+#             */
/*   Updated: 2025/08/13 22:16:23 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strtrim_in_place(char *str)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!str)
		return ;
	start = str;
	while (*start && ft_isspace(*start))
		start++;
	end = str + ft_strlen(str) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = (end - start) + 1;
	if (str != start)
		ft_memmove(str, start, len);
	str[len] = '\0';
}

void	mark_each(char *input, char *ret, int i)
{
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			i = is_append(ret, i);
		else if (input[i] == '<' && input[i + 1] == '<')
			i = is_heredoc(ret, i);
		else if (input[i] == '>')
			ret[i] = OUTPUT;
		else if (input[i] == '<')
			ret[i] = INPUT;
		else if (input[i] == '|')
			ret[i] = PIPE;
		else if (input[i] == '\"')
			ret[i] = DQUOTE;
		else if (input[i] == '\'')
			ret[i] = SQUOTE;
		else if (input[i] == 32)
			ret[i] = BLANK;
		else
			ret[i] = CHAR;
		i++;
	}
}

static int	fill_segment(t_mini *mini, int idx, int start, int end)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(mini->input);
	if (end < 0 || (size_t)end > len)
		end = (int)len;
	if (start < 0)
		start = 0;
	if (end < start)
		end = start;
	tmp = ft_substr(mini->input, start, end - start);
	if (!tmp)
		return (0);
	mini->sub_pipes[idx] = ft_strtrim(tmp, " ");
	free(tmp);
	return (mini->sub_pipes[idx] != NULL);
}

void	get_sub_pipes(t_mini *mini, int pipe_c, int x)
{
	int	idx;
	int	start;
	int	end;

	(void)x;
	if (!mini || !mini->input || (pipe_c > 0 && !mini->pipe_locs))
		return ;
	idx = 0;
	while (idx <= pipe_c)
	{
		if (idx == 0)
			start = 0;
		else
			start = mini->pipe_locs[idx - 1] + 1;
		if (idx == pipe_c)
			end = -1;
		else
			end = mini->pipe_locs[idx];
		if (!fill_segment(mini, idx, start, end))
			return ;
		idx++;
	}
}

char	*expand_variable(const char *input, int *i, char **menv)
{
	int		start;
	char	*var_name;
	char	*var_value;
	int		end;

	start = *i + 1;
	end = start;
	while (input[end] && (ft_isalnum(input[end]) || input[end] == '_'))
		end++;
	*i = end;
	var_name = ft_substr(input, start, end - start);
	if (!var_name)
		return (NULL);
	var_value = get_value(get_from_env(menv, var_name));
	if (!var_value)
	{
		free(var_name);
		return (NULL);
	}
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

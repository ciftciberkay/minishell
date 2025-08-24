/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:12:41 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:12:43 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_quoted(char *s, int i, int count)
{
	int	in_squote;
	int	in_dquote;
	int	is_word;

	in_squote = 0;
	in_dquote = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (!ft_strchr("\t ", s[i]) && (!in_squote && !in_dquote))
			is_word = 1;
		else if (ft_strchr("\t ", s[i]) && !in_squote && !in_dquote)
		{
			if (is_word && ++count)
				is_word = 0;
		}
		i++;
	}
	if (is_word)
		count++;
	return (count);
}

static int	skip_quote(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !*in_dquote)
	{
		*in_squote = !*in_squote;
		return (1);
	}
	if (c == '"' && !*in_squote)
	{
		*in_dquote = !*in_dquote;
		return (1);
	}
	return (0);
}

char	*rmv_quotes_mnly(char *word, int i, int j)
{
	char	*result;
	int		in_squote;
	int		in_dquote;

	if (!word)
		return (NULL);
	result = malloc(ft_strlen(word) + 1);
	if (!result)
		return (NULL);
	in_squote = 0;
	in_dquote = 0;
	while (word[i])
	{
		if (skip_quote(word[i], &in_squote, &in_dquote))
			i++;
		else
			result[j++] = word[i++];
	}
	result[j] = '\0';
	return (result);
}

static char	*get_next_word_quoted(char **s_ptr, int i, int start)
{
	int		in_squote;
	int		in_dquote;
	char	*word;
	char	*ret;

	in_squote = 0;
	in_dquote = 0;
	while (ft_strchr(" \t", (*s_ptr)[i]))
		i++;
	start = i;
	while ((*s_ptr)[i] && !(ft_strchr(" \t", (*s_ptr)[i])
	&& !in_squote && !in_dquote))
	{
		skip_quote((*s_ptr)[i], &in_squote, &in_dquote);
		i++;
	}
	word = ft_substr(*s_ptr, start, i - start);
	ret = rmv_quotes_mnly(word, 0, 0);
	free(word);
	if ((*s_ptr)[i])
		*s_ptr += i + 1;
	else
		*s_ptr += i;
	return (ret);
}

char	**ft_split_with_quotes(char *s, int j)
{
	char	**arr;
	int		word_count;
	char	*s_iter;

	if (!s)
		return (NULL);
	word_count = count_words_quoted(s, 0, 0);
	arr = malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	if (word_count > 0)
		s_iter = s;
	while (j < word_count)
	{
		arr[j] = get_next_word_quoted(&s_iter, 0, 0);
		if (!arr[j])
		{
			free_split(arr);
			return (NULL);
		}
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

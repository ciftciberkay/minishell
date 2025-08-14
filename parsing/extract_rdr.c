/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rdr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koraym <koraym@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:30:00 by koraym           #+#    #+#             */
/*   Updated: 2025/08/12 10:30:00 by koraym           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_redirect(t_redirects **head, char *temp_str, int *i,
	int type)
{
	char		*name;
	t_redirects	*new_node;

	name = get_redirect_name(temp_str, i);
	if (!name)
		return (0);
	new_node = create_redirect_node(type, name);
	free(name);
	if (!new_node)
		return (0);
	add_redirect_to_list(head, new_node);
	return (1);
}

static int	handle_character(t_redirects **head, char *temp_str, int *i,
	int *quotes)
{
	int	type;

	update_quote_status(temp_str[*i], &quotes[0], &quotes[1]);
	type = 0;
	if (!quotes[0] && !quotes[1])
		type = get_redirect_type(temp_str, i);
	if (type != 0)
	{
		if (!process_redirect(head, temp_str, i, type))
			return (0);
	}
	else
		(*i)++;
	return (1);
}

static t_redirects	*process_string(char *temp_str)
{
	t_redirects	*head;
	int			i;
	int			quotes[2];

	head = NULL;
	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (temp_str[i])
	{
		if (!handle_character(&head, temp_str, &i, quotes))
		{
			free_redirects(head);
			return (NULL);
		}
	}
	return (head);
}

t_redirects	*extract_redirects(char *sub_pipe_str)
{
	char		*temp_str;
	t_redirects	*result;

	temp_str = ft_strdup(sub_pipe_str);
	if (!temp_str)
		return (NULL);
	result = process_string(temp_str);
	free(temp_str);
	return (result);
}

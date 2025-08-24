/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rdr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:08:23 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:08:28 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_redirect(t_mini *mini, t_redirects **head, char *temp_str,
	int st[])
{
	char		*name;
	t_redirects	*new_node;

	name = get_redirect_name(mini, temp_str, &st[0]);
	if (!name)
		return (0);
	new_node = create_redirect_node(st[3], name);
	free(name);
	if (!new_node)
		return (0);
	add_redirect_to_list(head, new_node);
	return (1);
}

static int	handle_character(t_mini *mini, t_redirects **head, char *temp_str,
	int st[])
{
	int	type;

	update_quote_status(temp_str[st[0]], &st[1], &st[2]);
	type = 0;
	if (!st[1] && !st[2])
		type = get_redirect_type(temp_str, &st[0]);
	if (type != 0)
	{
		st[3] = type;
		if (!process_redirect(mini, head, temp_str, st))
			return (0);
	}
	else
		st[0]++;
	return (1);
}

static t_redirects	*process_string(t_mini *mini, char *temp_str)
{
	t_redirects	*head;
	int			st[4];

	head = NULL;
	st[0] = 0;
	st[1] = 0;
	st[2] = 0;
	st[3] = 0;
	while (temp_str[st[0]])
	{
		if (!handle_character(mini, &head, temp_str, st))
		{
			free_redirects(head);
			return (NULL);
		}
	}
	return (head);
}

t_redirects	*extract_redirects(t_mini *mini, char *sub_pipe_str)
{
	char		*temp_str;
	t_redirects	*result;

	temp_str = ft_strdup(sub_pipe_str);
	if (!temp_str)
		return (NULL);
	result = process_string(mini, temp_str);
	free(temp_str);
	return (result);
}

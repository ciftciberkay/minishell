/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:24:18 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 19:24:25 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirects	*create_redirect_node(int type, char *name)
{
	t_redirects	*new_redir;

	new_redir = malloc(sizeof(t_redirects));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->name = ft_strdup(name);
	if (!new_redir->name)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->exitflag = 1;
	new_redir->next = NULL;
	return (new_redir);
}

void	add_redirect_to_list(t_redirects **head, t_redirects *new_node)
{
	t_redirects	*current;

	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:14:57 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/09 20:31:10 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_command_node(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->ret = NULL;
	new_cmd->next = NULL;
	new_cmd->the_flag = 1;
	new_cmd->pid = 0;
	return (new_cmd);
}

void	add_command_to_list(t_command **head, t_command *new_node)
{
	t_command	*current;

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

static int	skip_redirect_and_name(char *str, int *i_ptr, char quote_char)
{
	int	i;

	i = *i_ptr;
	if (str[i + 1] == str[i])
		i += 2;
	else
		i += 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			process_quoted_string(str, &i, quote_char);
		else if (!ft_isspace(str[i]) && !is_redirect_char(str[i]))
			process_unquoted_string(str, &i);
		else
			break ;
	}
	*i_ptr = i;
	return (1);
}

void	cleanup_str_for_argv(char *str, int i, int j)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (is_redirect_char(str[i]))
		{
			if (!in_squote && !in_dquote)
			{
				skip_redirect_and_name(str, &i, 0);
				continue ;
			}
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
	ft_strtrim_in_place(str);
}

char	**extract_argv(char *sub_pipe_str)
{
	char	*cleaned_str;
	char	**argv;

	cleaned_str = ft_strdup(sub_pipe_str);
	if (!cleaned_str)
		return (NULL);
	cleanup_str_for_argv(cleaned_str, 0, 0);
	argv = ft_split_with_quotes(cleaned_str, ' ', 0);
	free(cleaned_str);
	return (argv);
}

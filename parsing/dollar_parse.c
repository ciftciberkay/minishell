/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:11:10 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:11:13 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_exitcode_ctx(t_dctx *c)
{
	char	*tmp;

	tmp = exitcode_dollar(c->mini->exitcode);
	c->res = ft_strjoin_free(c->res, tmp);
	c->i += 2;
}

static int	handle_dollar_quote_ctx(t_dctx *c)
{
	char	*tmp;
	int		start;
	int		old_i;

	if (c->sq || c->dq || !(c->in[c->i] == '$' && c->in[c->i + 1] == '"'
			&& c->in[c->i + 2]))
		return (0);
	old_i = c->i;
	c->i += 2;
	start = c->i;
	while (c->in[c->i] && c->in[c->i] != '"')
		c->i++;
	if (c->in[c->i] == '"')
	{
		tmp = ft_substr(c->in, start, c->i - start);
		if (tmp)
			c->res = ft_strjoin_free(c->res, tmp);
		c->i++;
		return (1);
	}
	c->i = old_i;
	return (0);
}

static void	init_ctx(t_dctx *c, const char *input, t_mini *mini)
{
	c->in = input;
	c->i = 0;
	c->sq = 0;
	c->dq = 0;
	c->mini = mini;
	c->res = ft_strdup("");
}

static char	*dollar_process_loop(t_dctx *c)
{
	if (!c->res)
		return (NULL);
	while (c->in[c->i])
	{
		if (c->in[c->i] == '\'' && !c->dq)
			handle_squote_ctx(c);
		else if (c->in[c->i] == '"' && !c->sq)
			handle_dquote_ctx(c);
		else if (handle_dollar_quote_ctx(c))
			;
		else if (!c->sq && c->in[c->i] == '$'
			&& (ft_isalnum(c->in[c->i + 1]) || c->in[c->i + 1] == '_'))
			handle_var_expand_ctx(c);
		else if (!c->sq && c->in[c->i] == '$' && c->in[c->i + 1] == '?')
			handle_exitcode_ctx(c);
		else
			append_one_ctx(c);
	}
	return (c->res);
}

char	*process_dollar_signs(const char *input, t_mini *mini)
{
	t_dctx	c;

	init_ctx(&c, input, mini);
	return (dollar_process_loop(&c));
}

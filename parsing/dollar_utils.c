/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook6 <macbook6@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:05:18 by macbook6          #+#    #+#             */
/*   Updated: 2025/08/13 22:07:59 by macbook6         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exitcode_dollar(int exitcode)
{
	char	*ret;

	ret = ft_itoa(exitcode);
	return (ret);
}

void	append_one_ctx(t_dctx *c)
{
	char	*tmp;

	tmp = ft_substr(c->in, c->i, 1);
	c->res = ft_strjoin_free(c->res, tmp);
	c->i++;
}

void	handle_squote_ctx(t_dctx *c)
{
	c->sq = !c->sq;
	append_one_ctx(c);
}

void	handle_dquote_ctx(t_dctx *c)
{
	c->dq = !c->dq;
	append_one_ctx(c);
}

void	handle_var_expand_ctx(t_dctx *c)
{
	char	*tmp;

	tmp = expand_variable(c->in, &c->i, c->mini->menv);
	if (!tmp)
		tmp = ft_strdup("");
	c->res = ft_strjoin_free(c->res, tmp);
}

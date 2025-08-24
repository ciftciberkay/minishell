/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:11:26 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:11:27 by femullao         ###   ########.fr       */
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

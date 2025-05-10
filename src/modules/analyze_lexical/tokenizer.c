/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:06:12 by teando            #+#    #+#             */
/*   Updated: 2025/05/10 22:27:09 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_lex.h"

static int	count_paren(t_shell *sh)
{
	t_list			*tokens;
	t_lexical_token	*token;
	size_t			l;
	size_t			r;

	l = 0;
	r = 0;
	tokens = sh->token_list;
	while (tokens->next)
	{
		token = (t_lexical_token *)tokens->data;
		if (token->type == TT_LPAREN)
			l++;
		if (token->type == TT_RPAREN)
			r++;
		tokens = tokens->next;
	}
	return (l == r);
}

t_status	mod_lex(t_shell *sh)
{
	sh->token_list = NULL;
	sh->status = E_NONE;
	if (!sh->source_line)
		return (sh->status = E_SYNTAX);
	if (!tokenize_line(sh))
		return (sh->status = E_SYNTAX);
	if (!count_paren(sh))
	{
		ft_dprintf(2, ES_TOKEN);
		return (sh->status = E_SYNTAX);
	}
	if (sh->debug & DEBUG_LEX)
		debug_print_token_list(sh->token_list);
	return (E_NONE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:08:24 by teando            #+#    #+#             */
/*   Updated: 2025/05/11 00:38:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_lex.h"

static char	*read_heredoc_body(char *delim, t_shell *sh)
{
	char	*body;
	char	*line;

	body = ms_strdup("", sh);
	while (42)
	{
		line = read_command_line("> ");
		if (!line || (!delim[0] && !line[0]) || !ft_strcmp(line, delim))
		{
			if (!line && g_signal_status != SIGINT)
				ft_dprintf(STDERR_FILENO, ES_WHD);
			if (line)
				xfree((void **)&line);
			break ;
		}
		if (g_signal_status == SIGINT)
		{
			sh->status = E_SIGINT;
			return (xfree((void **)&body), xfree((void **)&line), NULL);
		}
		body = xstrjoin_free2(body, line, sh);
		body = xstrjoin_free(body, "\n", sh);
	}
	return (body);
}

t_list	*handle_heredoc(t_lexical_token *tok, t_shell *sh)
{
	int		quoted;
	char	*delim;
	char	*body;

	if (!tok || !tok->value || !tok->value[0])
	{
		ft_dprintf(STDERR_FILENO, ES_TOKEN);
		free_token(tok);
		return (NULL);
	}
	quoted = is_quoted(tok->value);
	delim = trim_valid_quotes(tok->value, sh);
	body = read_heredoc_body(delim, sh);
	xfree((void **)&delim);
	if (!body)
		body = ms_strdup("", sh);
	xfree((void **)&tok->value);
	if (quoted)
		tok->type = TT_HEREDOC_NOEXP;
	tok->value = body;
	return (xlstnew(tok, sh));
}

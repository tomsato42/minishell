/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:06:12 by teando            #+#    #+#             */
/*   Updated: 2025/04/10 14:08:51 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_lex.h"

/**
 * @brief 入力されたソースラインをトークン化し、その構文を検証する
 *
 * @param shell 現在のシステム情報を保持するt_info構造体へのポインタ
 * @return トークン化および構文検証に成功した場合はE_NONEが返され、
 *         エラーが発生した場合は対応するステータスが返される
 *
 * @details
 * 1. shell->source_lineがNULLでないことを確認する
 * 2. tokenize_line関数を呼び出してソースラインをトークン化する
 * 3. トークン化に失敗した場合はステータスをE_SYNTAXに設定する
 * 4. validate_syntax関数を呼び出して、得られたトークンの構文を検証する
 * 5. すべての処理が成功した場合、E_NONEを返す
 */
t_status launch_lexer(t_shell *shell)
{
	shell->token_list = NULL;
	shell->status = E_NONE;
	if (!shell->source_line)
		return (shell->status);
	if (!tokenize_line(shell))
	{
		if (shell->status == E_NONE)
			shell->status = E_SYNTAX;
		return (shell->status);
	}
	return (shell->status);
}

/**
 * @brief トークンタイプを文字列表現に変換する
 *
 * @param t 変換するトークンタイプ
 * @return トークンタイプの文字列表現
 */
const char *type_to_str(t_token_type t)
{
	static const char *token_names[] = {
		[TT_WORD] = "TT_WORD",
		[TT_PIPE] = "TT_PIPE",
		[TT_REDIR_IN] = "TT_REDIR_IN",
		[TT_APPEND] = "TT_APPEND",
		[TT_REDIR_OUT] = "TT_REDIR_OUT",
		[TT_HEREDOC] = "TT_HEREDOC",
		[TT_LPAREN] = "TT_LPAREN",
		[TT_RPAREN] = "TT_RPAREN",
		[TT_AND_AND] = "TT_AND_AND",
		[TT_OR_OR] = "TT_OR_OR",
		[TT_SEMICOLON] = "TT_SEMICOLON",
		[TT_EOF] = "TT_EOF",
		[TT_ERROR] = "TT_ERROR"};

	if (t >= 0 && t <= TT_ERROR)
		return (token_names[t]);
	return ("TT_UNKNOWN");
}

/**
 * @brief デバッグ用にトークンリストの内容を表示する
 *
 * @param list 表示するトークンリスト
 */
void debug_print_token_list(t_list *list)
{
	t_lexical_token *tok;

	while (list)
	{
		tok = (t_lexical_token *)list->data;
		ft_printf("type: %s, value: ", type_to_str(tok->type));
		if (tok->value)
			ft_printf("[%s]\n", tok->value);
		else
			ft_printf("NULL\n");
		list = list->next;
	}
}

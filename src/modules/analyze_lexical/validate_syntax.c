#include "mod_lex.h"

/**
 * @brief 演算子トークンかどうかを判定する
 *
 * パイプや&&, ||, ;, 括弧など「演算子扱い」にするトークンを判定する。
 * リダイレクト等のトークンはここでは演算子として扱わない。
 * 括弧は演算子というよりはグルーピングトークンだが、構文チェックの
 * 目的で演算子として扱う。
 *
 * @param ttype 判定するトークンタイプ
 * @return 演算子トークンの場合は1、それ以外は0
 */
int is_operator_token(t_token_type ttype)
{
	if (ttype == TT_PIPE || ttype == TT_AND_AND || ttype == TT_OR_OR || ttype == TT_SEMICOLON || ttype == TT_LPAREN || ttype == TT_RPAREN)
		return (1);
	return (0);
}

/**
 * @brief エラートークンをチェックする
 *
 * トークンがエラートークン（TT_ERROR）かどうかをチェックし、
 * エラーの場合はinfo->statusにE_SYNTAXを設定する
 *
 * @param curr チェック対象のトークン
 * @param shell ステータスを保持するt_info構造体
 * @return エラーでない場合は1、エラーの場合は0
 */
static int check_error_token(t_lexical_token *curr, t_shell *shell)
{
	if (curr->type == TT_ERROR)
	{
		shell->status = E_SYNTAX;
		return (0);
	}
	return (1);
}

/**
 * @brief リダイレクトトークンをチェックする
 *
 * リダイレクトトークン（TT_REDIR_IN, TT_APPEND, TT_REDIR_OUT, TT_HEREDOC）の
 * value値が有効かどうかをチェックする。リダイレクトトークンはvalue値が
 * 必須であり、空文字列であってはならない。
 *
 * @param curr チェック対象のトークン
 * @param shell ステータスを保持するt_info構造体
 * @return 有効な場合は1、無効な場合は0
 */
static int check_redirect_token(t_lexical_token *curr, t_shell *shell)
{
	if (curr->type == TT_REDIR_IN || curr->type == TT_APPEND || curr->type == TT_REDIR_OUT || curr->type == TT_HEREDOC)
	{
		if (!curr->value || curr->value[0] == '\0')
		{
			shell->status = E_SYNTAX;
			return (0);
		}
	}
	return (1);
}

/**
 * @brief トークンリストの構文を検証する
 *
 * tokenize_line()で生成されたトークンリストの構文を検証する。
 * 現在は以下のチェックを行う：
 * 1. エラートークン（TT_ERROR）がないか
 * 2. リダイレクトトークンのvalue値が有効か
 *
 * @param shell トークンリストとステータスを保持するt_info構造体
 * @return 構文が正しい場合は1、エラーがある場合は0
 */
int validate_syntax(t_shell *shell)
{
	t_list *node;
	t_lexical_token *curr;

	node = shell->token_list;
	if (!node)
		return (1);
	while (node)
	{
		curr = (t_lexical_token *)node->data;
		if (!check_error_token(curr, shell))
			return (0);
		if (!check_redirect_token(curr, shell))
			return (0);
		node = node->next;
	}
	return (1);
}

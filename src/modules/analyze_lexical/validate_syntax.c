#include "mod_lex.h"

/*
 * 与えられたトークンタイプが演算子かどうかを判定する。
 * (現状では実装例として使っていないが、必要に応じて利用。)
 */
int is_operator_token(t_token_type ttype)
{
	if (ttype == TT_PIPE || ttype == TT_AND_AND || ttype == TT_OR_OR ||
		ttype == TT_SEMICOLON || ttype == TT_LPAREN || ttype == TT_RPAREN)
		return 1;
	return 0;
}

/*
 * トークンがエラータイプかどうかチェック。
 * エラータイプならシェルステータスをセットして失敗(0)を返す。
 */
static int validate_error_token(t_lexical_token *token, t_shell *shell)
{
	if (token->type == TT_ERROR)
	{
		shell->status = E_SYNTAX;
		return 0;
	}
	return 1;
}

/*
 * リダイレクト系トークンが引数を持たない場合はエラー。
 */
static int validate_redirect_token(t_lexical_token *token, t_shell *shell)
{
	if (token->type == TT_REDIR_IN || token->type == TT_APPEND ||
		token->type == TT_REDIR_OUT || token->type == TT_HEREDOC)
	{
		if (!token->value || token->value[0] == '\0')
		{
			shell->status = E_SYNTAX;
			return 0;
		}
	}
	return 1;
}

/*
 * トークンリスト全体を走査して、構文エラーなどをチェック。
 * エラーがあれば 0 を返す。正常なら 1。
 */
int validate_syntax(t_shell *shell)
{
	t_list *current_node = shell->token_list;
	if (!current_node)
		return 1; // トークンが空ならエラーではない(単に何もないだけ)

	while (current_node)
	{
		t_lexical_token *current_token = (t_lexical_token *)current_node->data;

		// エラートークンがある場合
		if (!validate_error_token(current_token, shell))
			return 0;

		// リダイレクト系トークンが不正でないか
		if (!validate_redirect_token(current_token, shell))
			return 0;

		current_node = current_node->next;
	}
	return 1;
}

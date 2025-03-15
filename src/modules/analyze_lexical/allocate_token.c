#include "mod_lex.h"

/**
 * @brief 指定されたトークンタイプと値を持つ新しいトークンを作成
 *
 * @param type トークンのタイプを指定する `t_token_type` 列挙型
 * @param value トークンに関連付ける文字列値
 * @param shell メモリ確保のために使用されるシェルの状態情報
 * @return 成功した場合は新しいトークンのポインタを返し、失敗した場合は NULL を返す
 */
t_token_type *create_token(t_token_type type, char *value, t_shell *shell)
{
	t_lexical_token *tok;

	tok = (t_lexical_token *)xmalloc(sizeof(t_lexical_token), shell);
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	return (tok);
}

/**
 * @brief トークンをトークンリストに追加
 *
 * @param shell トークンリストを保持する t_shell 構造体へのポインタ
 * @param tok 追加するトークンを指す t_lexical_token 構造体へのポインタ
 * @return 成功した場合は1を返し、失敗した場合は0を返す
 */
int add_token(t_shell *shell, t_lexical_token *tok)
{
	t_list *node;

	if (!tok)
		return (0);
	node = ft_lstnew(tok);
	if (!node)
	{
		free(tok->value);
		free(tok);
		return (0);
	}
	if (!shell->token_list)
		shell->token_list = node;
	else
		ft_lstadd_back(&shell->token_list, node);
	return (1);
}

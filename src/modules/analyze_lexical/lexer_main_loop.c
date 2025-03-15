#include "mod_lex.h"

/**
 * @brief 2項演算子 (TT_APPEND, TT_HEREDOC, TT_REDIR_IN, TT_REDIR_OUT) の演算子部と引数部をトークン化する
 *
 * 2項演算子の演算子部と引数部をトークン化し、shell->token_list に追加する
 *
 * @param op 2項演算子のトークンタイプ
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param shell トークン化結果を保持するt_info構造体
 */
static void handle_operator_with_arg(t_token_type op, const char *line,
									 size_t *pos, t_shell *shell)
{
	char *word;

	skip_spaces(line, pos);
	word = read_word(line, pos, shell);
	add_token(shell, create_token(op, word, shell));
}

/**
 * @brief 2文字演算子をトークン化する
 *
 * 2文字演算子 (TT_APPEND, TT_HEREDOC, TT_AND_AND, TT_OR_OR) をトークン化し、
 * shell->token_list に追加する
 *
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param shell トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗 (TT_ERROR)
 */
static int handle_two_char_op(const char *line, size_t *pos, t_shell *shell)
{
	t_token_type op;
	size_t len;

	op = get_two_char_op(&line[*pos], &len);
	if (op == TT_ERROR)
		return (0);
	(*pos) += len;
	if (op == TT_APPEND || op == TT_HEREDOC)
		handle_operator_with_arg(op, line, pos, shell);
	else
		add_token(shell, create_token(op, NULL, shell));
	return (1);
}

/**
 * @brief 1文字演算子をトークン化する
 *
 * 1文字演算子 (TT_REDIR_IN, TT_REDIR_OUT, TT_PIPE, TT_LPAREN, TT_RPAREN,
 * TT_SEMICOLON) をトークン化し、shell->token_list に追加する
 *
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param shell トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗 (TT_ERROR)
 */
static int handle_one_char_op(const char *line, size_t *pos, t_shell *shell)
{
	t_token_type op;

	op = get_one_char_op(line[*pos]);
	if (op == TT_ERROR)
		return (0);
	(*pos)++;
	if (op == TT_REDIR_IN || op == TT_REDIR_OUT)
		handle_operator_with_arg(op, line, pos, shell);
	else
		add_token(shell, create_token(op, NULL, shell));
	return (1);
}

/**
 * @brief 1トークンをトークン化する
 *
 * 指定されたソースライン中の1トークンをトークン化し、得られたトークンを
 * shell->token_listに追加する
 *
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param shell トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗 (TT_EOF)
 * @retval -1 トークン化に失敗 (E_SYNTAX)
 */
static int next_token(const char *line, size_t *pos, t_shell *shell)
{
	char *word;

	skip_spaces(line, pos);
	if (!line[*pos])
		return (add_token(shell, create_token(TT_EOF, NULL, shell)), 0);
	if (handle_two_char_op(line, pos, shell))
		return (1);
	if (handle_one_char_op(line, pos, shell))
		return (1);
	word = read_word(line, pos, shell);
	if (!word && shell->status == E_SYNTAX)
		return (-1);
	add_token(shell, create_token(TT_WORD, word, shell));
	return (1);
}

/**
 * @brief 1行をトークン化する
 *
 * source_lineフィールドに指定された1行をトークン化し、得られたトークンを
 * token_listフィールドに保持する
 *
 * @param shell トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗
 */
int tokenize_line(t_shell *shell)
{
	size_t i;
	int ret;
	const char *line;

	line = shell->source_line;
	shell->status = E_NONE;
	i = 0;
	while (1)
	{
		ret = next_token(line, &i, shell);
		if (ret == 0)
			break;
		if (ret < 0)
		{
			if (shell->status == E_NONE)
				shell->status = E_SYNTAX;
			return (0);
		}
	}
	return (1);
}

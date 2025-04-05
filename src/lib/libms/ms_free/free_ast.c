#include "libms.h"

/**
 * @brief 構文木の解放
 *
 * @param ast 解放する構文木へのポインタ
 */
void free_ast(t_ast *ast)
{
    if (!ast)
        return;

    // 子ノードの解放（再帰的）
    if (ast->left)
        free_ast(ast->left);
    if (ast->right)
        free_ast(ast->right);

    // データの解放（ノードタイプに応じて）
    if (ast->args)
    {
        // ノードタイプに応じた適切な解放処理
        if (ast->ntype == NT_CMD)
            free_command(ast->args);
        else if (ast->ntype == NT_REDIRECT)
            free_redirect(ast->args);
        // 他のタイプに応じた解放処理
    }

    free(ast);
}

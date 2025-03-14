/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:30:10 by teando            #+#    #+#             */
/*   Updated: 2025/03/14 15:48:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ms_token.h"
#include "ms_env.h"

/**
 * @brief シェルのクリーンアップ処理
 *
 * @param shell シェル構造体へのポインタ
 */
void shell_cleanup(t_shell *shell)
{
	int i;

	if (!shell)
		return;

	// モジュールのクリーンアップ
	if (shell->modules)
	{
		i = 0;
		while (i < MODULE_COUNT)
		{
			if (shell->modules->modules[i].loaded &&
				shell->modules->modules[i].cleanup)
				shell->modules->modules[i].cleanup(shell);
			i++;
		}
		free(shell->modules);
		shell->modules = NULL;
	}

	// リソースの解放
	if (shell->source_line)
	{
		free(shell->source_line);
		shell->source_line = NULL;
	}
	if (shell->token_list)
	{
		ft_lstclear(&shell->token_list, free_token);
		shell->token_list = NULL;
	}
	if (shell->ast)
	{
		free_ast(shell->ast);
		shell->ast = NULL;
	}

	// 環境変数のクリアは環境モジュールに移行予定
	if (shell->env_map)
	{
		ft_lstclear(&shell->env_map, free_env_var);
		shell->env_map = NULL;
	}

	// ファイルディスクリプタのクローズ
	if (shell->stdin_backup != -1)
	{
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
	if (shell->stdout_backup != -1)
	{
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
	if (shell->stderr_backup != -1)
	{
		close(shell->stderr_backup);
		shell->stderr_backup = -1;
	}
}

/**
 * @brief 環境変数の解放
 *
 * @param env_var 解放する環境変数へのポインタ
 */
#include "ms_env.h"

void free_env_var(void *env_var)
{
	t_env_var *var;

	if (!env_var)
		return;
	var = (t_env_var *)env_var;
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
}

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

/**
 * @brief シェルの終了処理
 *
 * @param shell シェル構造体へのポインタ
 * @param status 終了ステータス
 */
void shell_exit(t_shell *shell, int status)
{
	shell_cleanup(shell);
	exit(status);
}

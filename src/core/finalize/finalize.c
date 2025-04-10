/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:30:10 by teando            #+#    #+#             */
/*   Updated: 2025/04/10 18:58:38 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core.h"
#include "mod_env.h"

/**
 * @brief シェルのクリーンアップ処理
 *
 * @param shell シェル構造体へのポインタ
 */
void	shell_cleanup(t_shell *shell)
{
	if (!shell)
		return ;
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
 * @brief シェルの終了処理
 *
 * @param shell シェル構造体へのポインタ
 * @param status 終了ステータス
 */
void	shell_exit(t_shell *shell, int status)
{
	shell_cleanup(shell);
	exit(status);
}

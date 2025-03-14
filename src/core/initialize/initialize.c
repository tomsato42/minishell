/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:25:22 by teando            #+#    #+#             */
/*   Updated: 2025/03/14 15:46:18 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <limits.h>
/**
 * @brief シェル構造体の初期化
 *
 * @param shell シェル構造体へのポインタ
 * @param env 環境変数配列
 * @param module_flags 有効化するモジュールのフラグ
 * @return int 成功時0、エラー時-1
 */
int shell_init(t_shell *shell, char **env, int module_flags)
{
	if (!shell)
		return (-1);

	// シェル構造体の初期化
	ft_memset(shell, 0, sizeof(t_shell));
	shell->module_flags = module_flags;
	shell->status = E_NONE;
	shell->interactive = isatty(STDIN_FILENO);
	shell->exit_flag = 0;

	// 標準ファイルディスクリプタのバックアップ
	shell->stdin_backup = dup(STDIN_FILENO);
	if (shell->stdin_backup == -1)
		return (-1);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdout_backup == -1)
		return (-1);
	shell->stderr_backup = dup(STDERR_FILENO);
	if (shell->stderr_backup == -1)
		return (-1);

	// モジュールレジストリの初期化
	shell->modules = (t_module_registry *)malloc(sizeof(t_module_registry));
	if (!shell->modules)
		return (-1);
	ft_memset(shell->modules, 0, sizeof(t_module_registry));

	// シグナル初期化
	if (init_signals() != 0)
	{
		free(shell->modules);
		return (-1);
	}

	// カレントディレクトリの取得
	if (getcwd(shell->cwd, PATH_MAX) == NULL)
	{
		free(shell->modules);
		return (-1);
	}

	// モジュール初期化
	if (init_modules(shell, env) != 0)
	{
		free(shell->modules);
		return (-1);
	}

	return (0);
}

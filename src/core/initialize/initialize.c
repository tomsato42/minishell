/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:25:22 by teando            #+#    #+#             */
/*   Updated: 2025/04/10 18:48:31 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core.h"

/**
 * @brief シェル構造体の初期化
 *
 * @param shell シェル構造体へのポインタ
 * @param env 環境変数配列
 * @param module_flags 有効化するモジュールのフラグ
 * @return int 成功時0、エラー時-1
 */
int	shell_init(t_shell *shell, char **env, int module_flags)
{
	if (!shell)
		return (-1);
	// シェル構造体の初期化
	ft_bzero(shell, sizeof(t_shell));
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
	return (0);
}

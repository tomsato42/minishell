
#include "core.h"
#include "ms_module.h"
#include "ms_signal.h"

int main(int argc, char **argv, char **env)
{
	t_shell shell;

	(void)argc;
	(void)argv;

	// シグナルハンドラの初期化
	if (init_signals() != 0)
	{
		ft_putstr_fd("Error: Failed to initialize signal handlers\n",
					 STDERR_FILENO);
		return (1);
	}

	// シェルの初期化
	if (shell_init(&shell, env, MODULE_FLAG_MINIMAL) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize shell\n", STDERR_FILENO);
		return (1);
	}

	// インタラクティブモードの設定
	shell.interactive = isatty(STDIN_FILENO);

	// シェルループの実行
	shell_loop(&shell);

	// シェルのクリーンアップ
	shell_cleanup(&shell);

	return (shell.status);
}

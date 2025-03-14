#include "ms_readline.h"

/**
 * @brief シェルループの各ループ開始時の初期化
 *
 * @param shell シェル構造体へのポインタ
 */
static void line_init(t_shell *shell)
{
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
}

static void shell_loop(t_shell *shell, const char *prompt)
{
    while (1)
    {
        line_init(shell);

        shell->source_line = launch_readline(prompt);
        if (shell->source_line == NULL)
            shell_exit(shell, shell->status);
        if (g_signal_status == SIGINT)
        {
            g_signal_status = 0;
            free(shell->source_line);
            shell->source_line = NULL;
            continue;
        }
        int status = launch_lexer(shell) || launch_parser(shell) || launch_executor(shell);
        if (status != E_NONE)
            shell_exit(shell, status);
    }
}

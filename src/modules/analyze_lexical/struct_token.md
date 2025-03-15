# ms_token.h

```c
typedef enum e_token_type
{
/_ Command and Arguments _/
TT_WORD = 0x1101,

    /* Pipe */
    TT_PIPE = 0x302,

    /* Redirections */
    TT_REDIR_IN = 0x1201,
    TT_APPEND = 0x1202,
    TT_REDIR_OUT = 0x1203,
    TT_HEREDOC = 0x1204,

    /* Parentheses */
    TT_LPAREN = 0x501,
    TT_RPAREN = 0x502,

    /* Control Operators */
    TT_AND_AND = 0x2001,
    TT_OR_OR = 0x2002,
    TT_SEMICOLON = 0x2003,

    /* Special Tokens */
    TT_EOF = 0x2004,
    TT_ERROR = 0x002

} t_token_type;
```

```c
typedef struct s_lexical_token
{
    t_token_type type;
    char *value;
} t_lexical_token;
```

# core.h

```c

#include "ms_token.h"
#include "ms_ast.h"
#include "ms_readline.h"
#include "ms_signal.h"
#include "libft.h"
#include "libms.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

/*
** シグナルステータス
*/
extern volatile sig_atomic_t g_signal_status;

/*
** シェルステータス
*/
typedef enum e_status
{
    E_NONE = 0,
    E_ALLOCATE = 1,
    E_ENV_KEY = 1,
    E_SYNTAX = 1,
    E_PIPE = 1,
    E_FILE,
    E_ARGUMENT,
    E_NOT_BUITIN_CMD = -2,
    E_COMMAND_NOT_FOUND = 127,
    E_SIGINT = 130,
    E_SIGQUIT = 131,
} t_status;

/*
** シェル構造体
*/
typedef struct s_shell
{
    // コア状態
    char *source_line;  // 入力行
    t_list *token_list; // トークンリスト
    t_ast *ast;         // 構文木
    t_status status;    // 終了ステータス
    int exit_flag;      // 終了フラグ

    // 環境管理
    t_list *env_map;    // 環境変数マップ
    char *env_spc[128]; // 環境変数特殊文字
    char cwd[PATH_MAX]; // 現在作業ディレクトリ

    // リソース管理
    int stdin_backup;  // 標準入力バックアップ
    int stdout_backup; // 標準出力バックアップ
    int stderr_backup; // 標準エラー出力バックアップ

    // その他
    int interactive; // インタラクティブモード
    int debug;       // デバッグモード
} t_shell;

```

# 42-minishell 課題要件

## 必須要件（42 課題の範囲 + 複数行入力対応）

1. **C 言語**で実装し、**Norm**に準拠。
2. 例外(未定義動作)を除き、セグフォ等でのクラッシュがあってはならない。
3. メモリリークを許容しない（readline 由来のリークは除く）。
4. Makefile 要件（`NAME`, `all`, `clean`, `fclean`, `re`）。
5. **Libft**の使用が認められる。
6. **readline 系関数**を使用し、**ヒストリー**機能を実装する。
7. **環境変数**を正しく扱い、コマンド検索（`PATH`）を行う。
8. **グローバル変数**は「受け取ったシグナル番号を格納する 1 つのみ」に制限。
9. **シングルクォート**と**ダブルクォート**によるメタ文字の解釈と無効化。
10. **リダイレクト**
    - `<` 入力リダイレクト
    - `>` 出力リダイレクト(上書き)
    - `<<` (heredoc, ヒストリに追加しない)
    - `>>` 出力リダイレクト(追記)
11. **パイプ** (`|`) の実装。
12. **環境変数展開** `$VAR` や `$?` の対応。
13. **シグナル** `ctrl-C`, `ctrl-D`, `ctrl-\` の挙動
    - インタラクティブ時:
      - `ctrl-C`: 新しい行でプロンプトを再表示
      - `ctrl-D`: shell を終了
      - `ctrl-\`: 何もしない
14. **ビルトインコマンド**
    - `echo` (オプション `-n` のみ対応)
    - `cd` (相対・絶対パスのみ)
    - `pwd` (オプションなし)
    - `export` (オプションなし)
    - `unset` (オプションなし)
    - `env` (オプションや引数なし)
    - `exit` (オプションなし)
15. **複数行入力に対応**
    - 例: 「`||`」「`&&`」「パイプの途中で改行」などで、Bash のように次の行に入力を継続できる。
    - またはユーザが `\` で明示的に改行を継続するケースなど。
16. **ボーナス**
    - `&&`, `||`, `()` による複雑なコマンド制御
    - ワイルドカード `*`（カレントディレクトリ対象）

### 許容される関数

プログラム名：`minishell`

- 提出ファイル：`Makefile、*.h、*.c`
- Makefile：NAME、all、clean、fclean、re
- 引数：なし
- 外部関数：`readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs`
- Libft authorized Yes

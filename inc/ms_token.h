#ifndef MS_TOKEN_H
#define MS_TOKEN_H

#include "libft.h"
#include <limits.h>

typedef enum e_token_category
{
    CMD_ARG = 0x1000,
    CONNECT = 0x2000,
    REDIRECT = 0x1200,
    PAREN = 0x500,
    ERROR = 0x000
} t_token_category;

typedef enum e_token_type
{
    /* Command and Arguments */
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

typedef struct s_lexical_token
{
    t_token_type type;
    char *value;
} t_lexical_token;

/*
** ノードタイプ定義
*/
typedef enum e_ntype
{
	NT_CMD,
	NT_PIPE,
	NT_EOF,
	NT_AND,
	NT_OR,
	NT_REDIRECT
} t_ntype;

/*
** コマンド引数構造体
*/
typedef struct s_args
{
	char	path[PATH_MAX];
	char	**cargv;
	t_list	*argv;
	t_list	*redr;
	int	fds[2];
	pid_t	pid;
} t_args;

/*
** 抽象構文木構造体
*/
typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ntype		ntype;
	t_args		*args;
} t_ast;

/*
** トークン操作関数
*/
void	free_token(void *token);
void	free_ast(t_ast *ast);
void	free_command(t_args *args);
void	free_redirect(t_args *args);

#endif
#ifndef MS_READLINE_H
# define MS_READLINE_H

# include <readline/history.h>
# include <readline/readline.h>

// extern volatile sig_atomic_t g_signal_status;

char	*launch_readline(const char *prompt);

#endif

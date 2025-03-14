# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 01:37:23 by teando            #+#    #+#              #
#    Updated: 2025/03/14 15:50:57 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LFLAGS		:= -lreadline -L$(shell brew --prefix readline)/lib
	IDFLAGS		+= -I$(shell brew --prefix readline)/include
endif
ifeq ($(UNAME_S),Linux)
	LFLAGS		:= -lreadline
	IDFLAGS		+= -I/usr/include/readline
endif
RM			:= rm -rf

# ディレクトリ設定
ROOT_DIR	:= .
SRC_DIR		:= $(ROOT_DIR)/src
INC_DIR		:= $(ROOT_DIR)/inc
OBJ_DIR		:= $(ROOT_DIR)/obj
LIBFT_DIR	:= $(ROOT_DIR)/src/lib/libft
LIBMS_DIR	:= $(ROOT_DIR)/src/lib/libms

# ライブラリ設定
LIBFT		:= $(LIBFT_DIR)/libft.a
LIBMS		:= $(LIBMS_DIR)/libms.a

# インクルードフラグ
IDFLAGS		:= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBMS_DIR)

# ソースファイル
SRCS		:= \
	$(addprefix $(SRC_DIR)/, \
		main.c \
		$(addprefix core/, \
			$(addprefix initialize/, \
				initialize.c \
			) \
			$(addprefix finalize/, \
				finalize.c \
			) \
			$(addprefix signal/, \
				init_signals.c \
			) \
			$(addprefix module_api/, \
				module_api.c \
			) \
			shell_loop.c \
		) \
	)

# オブジェクトファイル
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ディレクトリの作成
$(OBJ_DIR)/core/initialize:
	mkdir -p $@

$(OBJ_DIR)/core/finalize:
	mkdir -p $@

$(OBJ_DIR)/core/signal:
	mkdir -p $@

$(OBJ_DIR)/core/module_api:
	mkdir -p $@

# ビルドルール
all: $(NAME)

$(NAME): $(LIBFT) $(LIBMS) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMS) $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/core/initialize $(OBJ_DIR)/core/finalize $(OBJ_DIR)/core/signal $(OBJ_DIR)/core/module_api
	$(CC) $(CFLAGS) $(IDFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMS):
	$(MAKE) -C $(LIBMS_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMS_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBMS_DIR) fclean

re: fclean all


# =======================
# == Submodule Targets ==
# =======================

$(LIBFT_DIR)/.init-stamp :
	git submodule update --init --recursive
	touch $@

sub:
	git submodule update --remote

norm:
	@norminette $(SRCS) $(INC_DIR)

.PHONY: all clean fclean re norm fclean_libft fclean_libms

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 15:50:22 by teando            #+#    #+#              #
#    Updated: 2025/03/14 22:59:09 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libms.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar
ARFLAGS		:= rcs
RM			:= rm -rf

# ディレクトリ設定
ROOT_DIR	:= ../..
INC_DIR		:= $(ROOT_DIR)/inc
OBJ_DIR		:= ./obj
LIBFT_DIR	:= ../libft

# インクルードフラグ
IDFLAGS		:= -I$(INC_DIR) -I$(LIBFT_DIR)

# ソースファイル
SRCS		:= \
	$(addprefix $(ROOT_DIR)/, \
		$(addprefix core/, \
			free_ast.c \
			free_token.c \
		) \
		$(addprefix x_rappers/, \
			xclose.c \
			xdup.c \
			xfork.c \
			xmalloc.c \
			xpipe.c \
			xstrs.c \
		) \
	)

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ディレクトリの作成
$(OBJ_DIR)/x_rappers:
	mkdir -p $@

# ビルドルール
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)/x_rappers
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IDFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	@norminette $(SRCS)

.PHONY: all clean fclean re norm

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2017/10/23 17:09:06 by gmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

INC_FLAGS = -I./includes/osx -I./libft/includes

INC_PATH = includes/osx

LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit

SRC_PATH = src

SRC_NAME = main.c init_map.c utilities.c draw_img.c raycaster.c intersect.c \
			inputs.c loop.c read_map.c init.c quit.c random_map.c

INC_NAME = wolf3d.h inputs_linux.h X.h

OBJ_PATH = obj

LIB_FLAGS = -L./libft

CC = clang

CFLAGS = -O2 -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./minilibx_macos
	@make -C ./libft --no-print-directory
	@$(CC) $(OBJ) -o $@ $(LIB_FLAGS) $(LIBS)
	@echo \[$(NAME)\] Compilation success

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC_PATH)/wolf3d.h $(INC_PATH)/inputs.h
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C ./libft clean --no-print-directory
	@echo \[$(NAME)\] .o files deleted
	make -C ./minilibx_macos clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean --no-print-directory
	@echo \[$(NAME)\] executable file deleted
	/bin/rm -f ./minilibx_macos/libmlx.a

re: fclean $(NAME)

.PHONY: all, clean, fclean, re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2017/10/23 16:54:19 by gmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstnew.c \
		ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_isblank.c\
		ft_memcpy.c ft_memdel.c ft_memmove.c ft_putchar.c ft_isspace.c\
		ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
		ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
		ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
		ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlen.c \
		ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
		ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
		ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
		ft_strlcat.c ft_lstdelone.c ft_lstdel.c ft_lstiter.c ft_lstmap.c \
		ft_lstpush_back.c ft_isupper.c ft_islower.c ft_realloc.c ft_isgraph.c \
		ft_lstlen.c get_next_line.c

HEADER = ./includes/libft.h

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $@
	@echo \[$(NAME)\] Compilation success

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -I ./includes -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	@echo \[$(NAME)\] .o files deleted

fclean: clean
	@/bin/rm -f $(NAME)
	@echo \[$(NAME)\] executable file deleted

re: fclean $(NAME)

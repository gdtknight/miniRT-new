# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#              #
#    Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I include -I libft/includes
LIBFT		= libft/libft.a
LIBS		= $(LIBFT) -lm

SRC			= src/main.c \
			  src/vector/vec_basic.c \
			  src/vector/vec_ops.c \
			  src/utils/ft_atof.c \
			  src/utils/get_next_line.c \
			  src/scene/scene.c \
			  src/parsing/parse_error.c \
			  src/parsing/parse_utils.c \
			  src/parsing/parse_scene.c \
			  src/parsing/parse_objects.c \
			  src/parsing/parse_file.c \
			  src/parsing/validate.c

OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

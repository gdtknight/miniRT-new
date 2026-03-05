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
INCLUDES	= -I include -I libft/includes -I minilibx
LIBFT		= libft/libft.a
MLX			= minilibx/libmlx.a
MLX_FLAGS	= -framework OpenGL -framework AppKit
LIBS		= $(LIBFT) $(MLX) $(MLX_FLAGS) -lm

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
			  src/parsing/validate.c \
			  src/window/window.c \
			  src/window/hooks.c \
			  src/window/image.c

OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx

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

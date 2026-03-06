# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoshin <yoshin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#              #
#    Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I include -I libft/includes -I minilibx
LIBFT       = libft/libft.a
MLX         = minilibx/libmlx.a
MLX_FLAGS   = -framework OpenGL -framework AppKit
LIBS        = $(LIBFT) $(MLX) $(MLX_FLAGS) -lm

SRC         = src/main.c \
              src/vector/vec_basic.c \
              src/vector/vec_ops.c \
              src/utils/ft_atof.c \
              src/utils/get_next_line.c \
              src/parsing/parse_error.c \
              src/parsing/parse_utils.c \
              src/parsing/parse_scene.c \
              src/parsing/parse_objects.c \
              src/parsing/parse_file.c \
              src/parsing/validate.c \
              src/scene/scene.c \
              src/scene/camera.c \
              src/window/window.c \
              src/window/hooks.c \
              src/window/image.c \
              src/render/ray.c \
              src/render/render.c \
              src/objects/sphere.c \
              src/objects/plane.c \
              src/objects/cylinder.c \
              src/objects/cylinder_caps.c

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

bonus:

.PHONY: all clean fclean re bonus

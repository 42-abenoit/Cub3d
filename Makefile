# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenoit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 20:39:13 by abenoit           #+#    #+#              #
#    Updated: 2020/09/22 19:20:51 by abenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OS_NAME := $(shell uname -s)

SRC_DIR = src

SRC_NAME =	main.c \
		ft_error.c \
		ft_error_2.c \
		ft_exit.c \
		str_utils.c \
		str_utils_2.c \
		lst_utils.c \
		lst_utils_2.c \
		mlx_utils.c \
		sprites_utils.c \
		ft_strtrim.c \
		ft_split.c \
		parse_trigger.c \
		parse_line.c \
		id_filler.c \
		id_filler_2.c \
		parse_map.c \
		control_map.c \
		game_struct.c \
		player_init.c \
		sprites.c \
		manage_key.c \
		move_set.c \
		move_set_2.c \
		render_engine.c \
		render_engine_ray.c \
		render_engine_img.c \
		bmp_save.c \
		bmp_export.c \
		rec_gnl.c


SRC = $(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

BONUS_DIR = bonus

NAME = Cub3D

INC = -I includes -I$(MLX_DIR)

CC = gcc
RM = rm -f

CFLAGS = -Wall -Werror -Wextra

MLX_DEF = -D $(OS_NAME)

MLX = libmlx.a

MLX_LIBS = -lmlx

MLX_INC = -L$(MLX_DIR)

MLX_DIR =
ifeq ($(OS_NAME),Darwin)
	MLX_DIR += mlx_macos
	MLX_INC += -framework OpenGL -framework AppKit
else
	MLX_DIR += mlx_linux
	MLX_LIBS += -lXext -lX11 -lm -lz
	KB_LAYOUT += $(shell setxkbmap -query | grep -oP "layout:\s+\K\w+")
endif

ifeq ($(KB_LAYOUT),fr)
	MLX_DEF += -D keyboard_fr
endif

all: $(MLX) $(NAME)

bonus:	$(MLX) bonus_make

bonus_make:
		@make -C $(BONUS_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	    $(CC) $(INC) $(CFLAGS) $(MLX_DEF) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(MLX_INC) $(MLX_LIBS)

$(MLX):
		@make -C $(MLX_DIR) $(MLX_LIBS)

clean:
		$(RM) -r $(OBJ_DIR)
		@make -C $(BONUS_DIR) clean

fclean:		clean
		$(RM) $(NAME)
		@make -C $(MLX_DIR) clean
		@make -C $(BONUS_DIR) fclean

re:		fclean all

.PHONY:	clean re fclean


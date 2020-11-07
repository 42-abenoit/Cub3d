# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenoit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 20:39:13 by abenoit           #+#    #+#              #
#    Updated: 2020/09/22 20:25:07 by abenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OS_NAME := $(shell uname -s)

SRC_DIR = src

SRC_NAME =	main_bonus.c \
		ft_error_bonus.c \
		ft_error_2_bonus.c \
		ft_exit_bonus.c \
		str_utils_bonus.c \
		str_utils_2_bonus.c \
		lst_utils_bonus.c \
		lst_utils_2_bonus.c \
		mlx_utils_bonus.c \
		sprites_utils_bonus.c \
		ft_strtrim_bonus.c \
		ft_split_bonus.c \
		parse_trigger_bonus.c \
		parse_line_bonus.c \
		id_filler_bonus.c \
		parse_map_bonus.c \
		control_map_bonus.c \
		game_struct_bonus.c \
		player_init_bonus.c \
		sprites_init_bonus.c \
		sprites_bonus.c \
		manage_key_bonus.c \
		manage_key_2_bonus.c \
		move_set_bonus.c \
		move_set_2_bonus.c \
		move_set_3_bonus.c \
		move_set_4_bonus.c \
		move_valid_bonus.c \
		render_engine_bonus.c \
		render_engine_ray_bonus.c \
		render_engine_ray_2_bonus.c \
		render_engine_img_bonus.c \
		floor_bonus.c \
		sky_bonus.c \
		sfx_bonus.c \
		player_char_bonus.c \
		player_anim_bonus.c \
		minimap_bonus.c \
		bmp_save_bonus.c \
		bmp_export_bonus.c \
		rec_gnl_bonus.c


SRC = $(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR = ../obj_bonus

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

NAME = ../Cub3D

INC = -I includes -I$(MLX_DIR) -I compatibility

CC = gcc
RM = rm -f

CFLAGS = -Wall -Werror -Wextra

MLX_DEF = -D $(OS_NAME)

MLX = libmlx.a

MLX_LIBS = -lmlx

MLX_INC = -L$(MLX_DIR)

MLX_DIR =
ifeq ($(OS_NAME),Darwin)
	MLX_DIR += ../mlx_macos
	MLX_INC += -framework OpenGL -framework AppKit
else
	INC += -lpthread
	MLX_DIR += ../mlx_linux
	MLX_LIBS += -lXext -lX11 -lm -lz
	KB_LAYOUT += $(shell setxkbmap -query | grep -oP "layout:\s+\K\w+")
endif

ifeq ($(KB_LAYOUT),fr)
	MLX_DEF += -D keyboard_fr
endif

all: $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
ifeq (%.c, render_engine_bonus.c)
	$(eval INC += -lpthread)
endif
ifeq (%.c, sprites_bonus.c)
	$(eval INC += -lpthread)
endif
	    $(CC) $(INC) $(CFLAGS) $(MLX_DEF) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(MLX_INC) $(MLX_LIBS)

clean:
		$(RM) -r $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: clean re fclean


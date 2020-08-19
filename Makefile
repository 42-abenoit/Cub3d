# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenoit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 20:39:13 by abenoit           #+#    #+#              #
#    Updated: 2020/08/19 17:55:26 by abenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src

SRC_NAME =	main.c \
		ft_error.c \
		ft_exit.c \
		str_utils.c \
		str_utils_2.c \
		ft_strtrim.c \
		ft_split.c \
		parse_trigger.c \
		parse_line.c \
		id_filler.c \
		rec_gnl.c


SRC = $(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

NAME = Cub3d

INC = -I includes

CC = gcc
RM = rm -f

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	    $(CC) $(INC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC)

clean:
		$(RM) -r $(OBJ_DIR)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	clean re fclean


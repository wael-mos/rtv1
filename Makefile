# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 16:58:40 by wael-mos          #+#    #+#              #
#    Updated: 2019/05/23 14:48:39 by wael-mos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= rtv1

# Directories

SRC_DIR	:= ./srcs
LIB_DIR	:= ./minilibx_macos
OBJ_DIR	:= ./obj

# SRC/OBJ files

SRC		:= 	*.c

OBJ		:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Few flags

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra # -O2 -g

#

.PHONY:		clean fclean all re

all:
	@mkdir -p $(OBJ_DIR)
	@make -C minilibx_macos/
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(LIB_DIR) -o $@ -c $<
	@printf "\r\033[K"
	@printf "Compiling object: $@ [ ✔ ]"

$(NAME): 	$(OBJ)
	@$(CC) $(CFLAGS) -I $(LIB_DIR) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lmlx \
		-framework OpenGL -framework AppKit

clean:
	@make -C minilibx_macos/ clean
	@/bin/rm -rf $(OBJ_DIR)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean"

fclean:		clean
	@/bin/rm -rf $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean"

re:			fclean all

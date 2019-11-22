# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 18:30:20 by jnovotny          #+#    #+#              #
#    Updated: 2019/11/22 10:26:08 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_GREEN = \033[1;32m
C_BLUE = \033[1;34m
C_L_BLUE = \033[1;34m
C_WHITE = \033[1;37m
C_RES = \033[0m

NAME = jnovotny.filler

LIB = ../printf/libftprintf.a

FTS =	main.c \
		datafeed.c \
		error.c \
		tools.c \
		printer.c \
		place_token.c

FTO = $(FTS.c=.o)

LIB_I = ../printf/includes/

I_DIR = ./includes/
S_DIR = ./srcs/
O_DIR = ./objs/

SRCS = $(addprefix $(S_DIR), $(FTS))

CFLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re libft

all: $(NAME)

libft:
	@make -C ../printf

$(NAME):
	@/bin/mkdir -p $(O_DIR)
	@gcc -o $(NAME) $(CFLAGS) -I$(I_DIR) -I$(LIB_I) $(LIB) $(SRCS)
	@echo "$(C_GREEN)[$(C_BLUE)$(NAME)$(C_GREEN) was compiled]$(C_RES)"

clean:
	@/bin/rm -rf $(O_DIR)
	@echo "$(C_RED)[Objects deleted!]$(C_RES)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(C_RED)[Removed $(NAME)]$(C_RES)"

re: fclean all


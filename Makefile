# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 18:30:20 by jnovotny          #+#    #+#              #
#    Updated: 2019/12/11 20:46:45 by jnovotny         ###   ########.fr        #
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

LIB = ./library/libftprintf.a

FTS =	calculus_tools.c \
		corners.c\
		datafeed.c \
		e_points.c \
		edge_strat.c \
		error.c \
		fetch_data.c \
		ft_sqrt_prec.c \
		gg_img.c \
		gg_img2.c \
		main.c \
		map_parse.c \
		mlx_control.c \
		place_token.c \
		place_token2.c \
		printer.c \
		scoring.c \
		strat_adjust.c \
		strat_adjust2.c \
		strat_supp.c \
		str_supp2.c \
		tools.c \
		tools2.c \
		vectors.c \
		visual_bg.c \
		visual_img.c \
		visualizator.c
		

FTO = $(FTS.c=.o)

LIB_I = ./library/includes/

I_DIR = ./includes/
S_DIR = ./srcs/
O_DIR = ./objs/

SRCS = $(addprefix $(S_DIR), $(FTS))

CFLAGS = -Wall -Werror -Wextra -O3

GRAPHIC = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re libft

all: $(NAME)

libft:
	@make -C ./library

$(NAME): libft
	@gcc -o $(NAME) $(CFLAGS) -I$(I_DIR) -I$(LIB_I) $(LIB) $(GRAPHIC) $(SRCS)
	@echo "$(C_GREEN)[$(C_BLUE)$(NAME)$(C_GREEN) was compiled]$(C_RES)"

clean:
	@make clean -C ./library
	@/bin/rm -rf $(O_DIR)
	@echo "$(C_RED)[Objects deleted!]$(C_RES)"

fclean: clean
	@make fclean -C ./library
	@/bin/rm -f $(NAME)
	@echo "$(C_RED)[Removed $(NAME)]$(C_RES)"

re: fclean all


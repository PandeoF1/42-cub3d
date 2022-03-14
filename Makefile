# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by tnard             #+#    #+#              #
#    Updated: 2022/03/14 13:22:08 by tnard            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		= cub3d.c srcs/check/ft_check_arg.c srcs/check/ft_check_map.c \
				srcs/check/ft_check_texture.c srcs/check/ft_get_file.c \
				srcs/check/ft_max_len.c srcs/utils/ft_strnjoin.c \
				srcs/utils/ft_free_split.c srcs/utils/ft_splitlen.c \
				srcs/event/ft_key_event.c srcs/event/ft_move.c 

NAME		= cub3d

ifeq ($(OS),Darwin)
	minilibx	= mlbx-macos/libmlx.a
	MLB_FLAGS	= -framework OpenGL -framework AppKit -framework OpenAL libft/libft.a ft_printf/libftprintf.a 
else
	minilibx	= mlbx-linux/libmlx.a
	MLB_FLAGS	= -lpthread -I -g -L /usr/X11/lib -Lincludes -L./mlbx-linux -lmlx -Imlx -lXext -lX11 -lz -lm libft/libft.a ft_printf/libftprintf.a 
endif

OBJS_DIR	= objs/
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= -O3 -Ofast -flto -march=native -ffast-math #-g3 -fsanitize=address #-Wall -Werror -Wextra -g3

$(OBJS_DIR)%.o : %.c includes/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@mkdir -p $(OBJS_DIR)srcs/utils
	@mkdir -p $(OBJS_DIR)srcs/check
	@mkdir -p $(OBJS_DIR)srcs/event
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

maker:
	@make -C libft
	@make -C ft_printf
ifeq ($(OS),Darwin)
	@make -C mlbx-macos
else
	@make -C mlbx-linux
endif

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libft
	@make clean -C ft_printf
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make fclean -C ft_printf
ifeq ($(OS),Darwin)
	@make clean -C mlbx-macos
else
	@make clean -C mlbx-linux
endif
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all
.PHONY:		all clean fclean re
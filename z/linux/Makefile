# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by tnard             #+#    #+#              #
#    Updated: 2022/04/12 09:41:45 by tnard            ###   ########lyon.fr    #
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
				srcs/event/ft_key_event.c srcs/event/ft_move.c \
				srcs/set/ft_set.c srcs/put_texture/ft_put_texture.c \
				srcs/check/ft_check_is.c srcs/create_plan/ft_create_plan.c \
				srcs/door/ft_door.c srcs/map_fps_pos/ft_map.c \
				srcs/utils/ft_music.c srcs/init/ft_create.c \
				srcs/img_fct/ft_img_init.c srcs/init/ft_init.c \
				srcs/map_fps_pos/ft_pos.c srcs/utils/ft_nb_of.c \
				srcs/img_fct/ft_img_utils.c srcs/utils/ft_end.c \
				srcs/utils/ft_split_number.c srcs/event/ft_mouse.c \
				srcs/update/ft_update.c srcs/update/ft_update_2.c \
				srcs/img_fct/ft_reverse_flip_img.c srcs/utils/ft_gettime.c \
				srcs/map_fps_pos/ft_fps.c

NAME		= cub3d
minilibx	= mlbx/libmlx.a
OBJS_DIR	= objs/
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= -O3 -Ofast -flto -march=native -ffast-math -Wall -Werror -Wextra -lpthread
MLB_FLAGS	= -I -g -L /usr/X11/lib -Lincludes -L./mlbx -lmlx -Imlx -lXext -lX11 -lz -lm libft/libft.a ft_printf/libftprintf.a

$(OBJS_DIR)%.o : %.c includes/cub3d.h
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(NAME): file $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

file:
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@mkdir -p $(OBJS_DIR)srcs/utils
	@mkdir -p $(OBJS_DIR)srcs/check
	@mkdir -p $(OBJS_DIR)srcs/event
	@mkdir -p $(OBJS_DIR)srcs/set
	@mkdir -p $(OBJS_DIR)srcs/put_texture
	@mkdir -p $(OBJS_DIR)srcs/create_plan
	@mkdir -p $(OBJS_DIR)srcs/door
	@mkdir -p $(OBJS_DIR)srcs/map_fps_pos
	@mkdir -p $(OBJS_DIR)srcs/init
	@mkdir -p $(OBJS_DIR)srcs/img_fct
	@mkdir -p $(OBJS_DIR)srcs/update

maker:
	@make -C mlbx
	@make -C libft
	@make -C ft_printf

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libft
	@make clean -C ft_printf
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make clean -C mlbx
	@make fclean -C libft
	@make fclean -C ft_printf
	@rm -f $(NAME)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re

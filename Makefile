# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by tnard             #+#    #+#              #
#    Updated: 2022/04/06 11:34:01 by asaffroy         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

ifeq ($(OS),Darwin)
	SRCS		= MACOS/cub3d.c srcs/check/ft_check_arg.c MACOS/srcs/check/ft_check_map.c \
				MACOS/srcs/check/ft_check_texture.c MACOS/srcs/check/ft_get_file.c \
				MACOS/srcs/check/ft_max_len.c MACOS/srcs/utils/ft_strnjoin.c \
				MACOS/srcs/utils/ft_free_split.c MACOS/srcs/utils/ft_splitlen.c \
				MACOS/srcs/event/ft_key_event.c MACOS/srcs/event/ft_move.c \
				MACOS/srcs/set/ft_set.c MACOS/srcs/put_texture/ft_put_texture.c \
				MACOS/srcs/check/ft_check_is.c MACOS/srcs/create_plan/ft_create_plan.c \
				MACOS/srcs/door/ft_door.c MACOS/srcs/map_fps_pos/ft_map.c \
				MACOS/srcs/utils/ft_music.c MACOS/srcs/init/ft_create.c \
				MACOS/srcs/img_fct/ft_img_init.c MACOS/srcs/init/ft_init.c \
				MACOS/srcs/map_fps_pos/ft_pos.c MACOS/srcs/utils/ft_nb_of.c \
				MACOS/srcs/img_fct/ft_img_utils.c MACOS/srcs/utils/ft_end.c \
				MACOS/srcs/utils/ft_split_number.c MACOS/srcs/event/ft_mouse.c \
				MACOS/srcs/update/ft_update.c MACOS/srcs/update/ft_update_2.c \
				MACOS/srcs/img_fct/ft_reverse_flip_img.c MACOS/srcs/utils/ft_gettime.c \
				MACOS/srcs/map_fps_pos/ft_fps.c
else
	SRCS		= LINUX/cub3d.c LINUX/srcs/check/ft_check_arg.c LINUX/srcs/check/ft_check_map.c \
				LINUX/srcs/check/ft_check_texture.c LINUX/srcs/check/ft_get_file.c \
				LINUX/srcs/check/ft_max_len.c LINUX/srcs/utils/ft_strnjoin.c \
				LINUX/srcs/utils/ft_free_split.c LINUX/srcs/utils/ft_splitlen.c \
				LINUX/srcs/event/ft_key_event.c LINUX/srcs/event/ft_move.c \
				LINUX/srcs/set/ft_set.c LINUX/srcs/put_texture/ft_put_texture.c \
				LINUX/srcs/check/ft_check_is.c LINUX/srcs/create_plan/ft_create_plan.c \
				LINUX/srcs/door/ft_door.c LINUX/srcs/map_fps_pos/ft_map.c \
				LINUX/srcs/utils/ft_music.c LINUX/srcs/init/ft_create.c \
				LINUX/srcs/img_fct/ft_img_init.c LINUX/srcs/init/ft_init.c \
				LINUX/srcs/map_fps_pos/ft_pos.c LINUX/srcs/utils/ft_nb_of.c \
				LINUX/srcs/img_fct/ft_img_utils.c LINUX/srcs/utils/ft_end.c \
				LINUX/srcs/utils/ft_split_number.c LINUX/srcs/event/ft_mouse.c \
				LINUX/srcs/update/ft_update.c LINUX/srcs/update/ft_update_2.c \
				LINUX/srcs/img_fct/ft_reverse_flip_img.c LINUX/srcs/utils/ft_gettime.c \
				LINUX/srcs/map_fps_pos/ft_fps.c
endif

NAME		= cub3d
OS			= $(shell uname -s)
ifeq ($(OS),Darwin)
	header		= MACOS/includes/cub3d.h
	minilibx	= mlbx-macos/libmlx.a
	MLB_FLAGS	= -Lincludes -framework OpenGL -framework AppKit -framework OpenAL libft/libft.a ft_printf/libftprintf.a 
else
	header		= LINUX/includes/cub3d.h
	minilibx	= mlbx-linux/libmlx.a
	MLB_FLAGS	= -lpthread -I -g -L /usr/X11/lib -Lincludes -L./mlbx-linux -lmlx -Imlx -lXext -lX11 -lz -lm libft/libft.a ft_printf/libftprintf.a 
endif

OBJS_DIR	= objs/
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= -O3 -Ofast -flto -march=native -ffast-math#-g3 -fsanitize=address #-Wall -Werror -Wextra -g3

ifeq ($(OS),Darwin)
$(OBJS_DIR)%.o : %.c MACOS/includes/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)MACOS
	@mkdir -p $(OBJS_DIR)LINUX
	@mkdir -p $(OBJS_DIR)LINUX/srcs
	@mkdir -p $(OBJS_DIR)LINUX/srcs/utils
	@mkdir -p $(OBJS_DIR)LINUX/srcs/check
	@mkdir -p $(OBJS_DIR)LINUX/srcs/event
	@mkdir -p $(OBJS_DIR)LINUX/srcs/set
	@mkdir -p $(OBJS_DIR)LINUX/srcs/put_texture
	@mkdir -p $(OBJS_DIR)LINUX/srcs/create_plan
	@mkdir -p $(OBJS_DIR)LINUX/srcs/door
	@mkdir -p $(OBJS_DIR)LINUX/srcs/map_fps_pos
	@mkdir -p $(OBJS_DIR)LINUX/srcs/init
	@mkdir -p $(OBJS_DIR)LINUX/srcs/img_fct
	@mkdir -p $(OBJS_DIR)LINUX/srcs/update
	@mkdir -p $(OBJS_DIR)MACOS/srcs
	@mkdir -p $(OBJS_DIR)MACOS/srcs/utils
	@mkdir -p $(OBJS_DIR)MACOS/srcs/check
	@mkdir -p $(OBJS_DIR)MACOS/srcs/event
	@mkdir -p $(OBJS_DIR)MACOS/srcs/set
	@mkdir -p $(OBJS_DIR)MACOS/srcs/put_texture
	@mkdir -p $(OBJS_DIR)MACOS/srcs/create_plan
	@mkdir -p $(OBJS_DIR)MACOS/srcs/door
	@mkdir -p $(OBJS_DIR)MACOS/srcs/map_fps_pos
	@mkdir -p $(OBJS_DIR)MACOS/srcs/init
	@mkdir -p $(OBJS_DIR)MACOS/srcs/img_fct
	@mkdir -p $(OBJS_DIR)MACOS/srcs/update
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"
else
$(OBJS_DIR)%.o : %.c LINUX/includes/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)MACOS
	@mkdir -p $(OBJS_DIR)LINUX
	@mkdir -p $(OBJS_DIR)LINUX/srcs
	@mkdir -p $(OBJS_DIR)LINUX/srcs/utils
	@mkdir -p $(OBJS_DIR)LINUX/srcs/check
	@mkdir -p $(OBJS_DIR)LINUX/srcs/event
	@mkdir -p $(OBJS_DIR)LINUX/srcs/set
	@mkdir -p $(OBJS_DIR)LINUX/srcs/put_texture
	@mkdir -p $(OBJS_DIR)LINUX/srcs/create_plan
	@mkdir -p $(OBJS_DIR)LINUX/srcs/door
	@mkdir -p $(OBJS_DIR)LINUX/srcs/map_fps_pos
	@mkdir -p $(OBJS_DIR)LINUX/srcs/init
	@mkdir -p $(OBJS_DIR)LINUX/srcs/img_fct
	@mkdir -p $(OBJS_DIR)LINUX/srcs/update
	@mkdir -p $(OBJS_DIR)MACOS/srcs
	@mkdir -p $(OBJS_DIR)MACOS/srcs/utils
	@mkdir -p $(OBJS_DIR)MACOS/srcs/check
	@mkdir -p $(OBJS_DIR)MACOS/srcs/event
	@mkdir -p $(OBJS_DIR)MACOS/srcs/set
	@mkdir -p $(OBJS_DIR)MACOS/srcs/put_texture
	@mkdir -p $(OBJS_DIR)MACOS/srcs/create_plan
	@mkdir -p $(OBJS_DIR)MACOS/srcs/door
	@mkdir -p $(OBJS_DIR)MACOS/srcs/map_fps_pos
	@mkdir -p $(OBJS_DIR)MACOS/srcs/init
	@mkdir -p $(OBJS_DIR)MACOS/srcs/img_fct
	@mkdir -p $(OBJS_DIR)MACOS/srcs/update
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"
endif

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
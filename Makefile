# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thuynguy <thuynguy@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2023/08/15 21:17:23 by thuynguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
NAME_BONUS = cub3D_bonus
# RAY_CASTER := raycast_build

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
LINKS = -lmlx -framework OpenGL -framework AppKit
#CDEBUG = -fsanitize=address

DIR_DUP     = mkdir -p $(@D)
# SRC = cub3D_main.c \
# 	cub3D_utils.c \
# 	cub3D_map.c \

SRC := raycast/raycast_start.c raycast/calculate_rays.c raycast/draw_raycast_view.c \
		 drawing_utils/ft_bresenham.c \
		 drawing_utils/drawing_utils1.c \
		 clean_exit/ft_mlx_close.c \
		 events/handle_press.c \
		 images/ft_images.c \
		 player/setup_player.c player/player_move.c player/draw_player.c \
		 utils_2.c \
		 redraw.c \
		 setup/setup_cubed.c setup/setup_raycast.c \
		 texture/cub3D_texture.c \
		 
SRC += cub3D_main.c \
	parsing/cub3D_utils.c \
	parsing/cub3D_map.c \
	parsing/cub3D_map_elems.c \
	parsing/cub3D_map_content.c \
	parsing/cub3D_map_valid.c \
	parsing/cub3D_parsing_utils.c \
	parsing/debug.c \

BONUS = draw_minimap.c \
		draw_raycast_view_bonus.c \
		raycast_start_bonus.c \
# BOUNUS_SRC
# BOUNUS_OBJS

SRCFD = srcs/
SRCFD_BONUS = srcs/bonus/
OBJSFD = objs/
OBJSFD_BONUS = objs_bonus/
SRCS	= $(addprefix $(SRCFD), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJSFD),$(OBJ))

ALL_BONUS_SRCS := $(filter-out raycast/raycast_start.c raycast/draw_raycast_view.c, $(SRC))
ALL_BONUS_SRCS += $(BONUS)
OBJS_BONUS = $(patsubst %, $(OBJSFD_BONUS)%, $(ALL_BONUS_SRCS:.c=.o))
# R_SRCS	:= $(addprefix $(SRCFD), $(R_SRC))
# R_OBJ := $(R_SRCS:.c=.o)
# R_OBJS = $(addprefix $(OBJSFD),$(R_OBJ))

HEADER_PATH = -I ./includes
HEADER_PATH_BONUS = -I ./includes_bonus
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

LIBS = -Llibft -lft

.PHONY : all clean fclean re

all : $(NAME)

$(OBJSFD)%.o: $(SRCFD)%.c
	@mkdir -p $(OBJSFD)
	$(DIR_DUP)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CDEBUG) $(LIBS) $(LINKS) $^ -o $@

bonus: $(NAME_BONUS)
	
$(OBJSFD_BONUS)%.o: $(SRCFD_BONUS)%.c
	@mkdir -p $(OBJSFD_BONUS)
	$(DIR_DUP)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(CDEBUG) $(LIBS) $(LINKS) $^ -o $@

$(LIBFT) :
	make -C $(LIBFT_PATH)

clean :
	rm -rf $(OBJSFD) $(OBJSFD_BONUS)
	make fclean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

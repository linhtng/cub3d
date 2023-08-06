# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2023/08/06 19:13:37 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
# RAY_CASTER := raycast_build

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
LINKS = -lmlx -framework OpenGL -framework AppKit

DIR_DUP     = mkdir -p $(@D)
# SRC = cub3D_main.c \
# 	cub3D_utils.c \
# 	cub3D_map.c \

SRC := ray_cast_main.c \
		 drawing_utils/ft_bresenham.c \
		 draw_minimap.c \
		 drawing_utils/drawing_utils1.c \
		 ft_mlx_close.c \
		 handle_press.c \
		 raycast/calculate_rays.c \
		 raycast/draw_raycast_view.c \
		 ft_images.c \
		 utils_2.c \
		 player/setup_player.c \
		 

SRCFD = srcs/
OBJSFD = objs/
SRCS	= $(addprefix $(SRCFD), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJSFD),$(OBJ))

# R_SRCS	:= $(addprefix $(SRCFD), $(R_SRC))
# R_OBJ := $(R_SRCS:.c=.o)
# R_OBJS = $(addprefix $(OBJSFD),$(R_OBJ))

HEADER_PATH = -I ./includes
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
	$(CC) $(CFLAGS) $(LIBS) $(LINKS) $^ -o $@

$(LIBFT) :
	make -C $(LIBFT_PATH)

clean :
	rm -rf $(OBJSFD)
	make fclean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

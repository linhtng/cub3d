# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2023/07/20 14:42:09 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
# RAY_CASTER := raycast_build

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
LINKS = -lmlx -framework OpenGL -framework AppKit

# SRC = cub3D_main.c \
# 	cub3D_utils.c \
# 	cub3D_map.c \

SRC := ray_cast_main.c \
		 ft_bresenham.c \
		 draw_minimap.c \
		 drawing_utils1.c \
		 ft_mlx_close.c \
		 handle_press.c \
		 calculate_rays.c \

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

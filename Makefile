# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2022/11/22 15:30:31 by thuynguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
LINKS = -lmlx -framework OpenGL -framework AppKit

SRC = 

OBJ = $(SRC:.c=.o)
HEADERS = include/cub3D.h

HEADER_PATH = ./include
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

LIBS = -Llibft -lft

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(HEADER_PATH) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ) : $(HEADERS)

$(LIBFT) :
	make -C $(LIBFT_PATH)

clean :
	rm -f $(OBJ)
	make fclean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

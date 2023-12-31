# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2023/09/20 11:12:04 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
NAME_BONUS = cub3D_bonus

# Color Aliases
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
YELLOW = '\033[0;93m'

CFLAGS = -Wall -Wextra -Werror -g3 -I ./includes
BONUS_CFLAGS = -Wall -Wextra -Werror -g3 -I ./includes_bonus
CC = cc
LINKS = -lmlx -framework OpenGL -framework AppKit
# CDEBUG = -fsanitize=address

RAYCAST_DIR = srcs/raycast/
DRAWING_DIR = srcs/drawing_utils/
EXIT_DIR = srcs/clean_exit/
EVENT_DIR = srcs/events/
IMG_DIR = srcs/images/
PLAYER_DIR = srcs/player/
SETUP_DIR = srcs/setup/
TEXTURE_DIR = srcs/texture/
MAIN_DIR = srcs/main/
PARSE_DIR = srcs/parsing/
BONUS_DIR = srcs/bonus/

RAYCAST = raycast_start.c calculate_rays.c draw_raycast_view.c
DRAWING = drawing_utils1.c
EXIT = ft_mlx_close.c
EVENT = handle_press.c
IMG = ft_images.c
PLAYER = setup_player.c player_move.c 
SETUP = setup_cubed.c setup_raycast.c init_scene.c
TEXTURE = cub3D_texture.c
MAIN = cub3D_main.c utils_2.c redraw.c
PARSING = valid_texture_utils.c cub3D_utils.c cub3D_map.c cub3D_map_elems.c cub3D_map_content.c cub3D_map_valid.c cub3D_parsing_utils.c debug.c
 
ALL_SRCS = $(RAYCAST) $(DRAWING) $(EXIT) $(EVENT) $(IMG) $(PLAYER) $(SETUP) $(TEXTURE) $(MAIN) $(PARSING)

BONUS = draw_minimap_bonus.c \
		draw_player_bonus.c \
		draw_raycast_view_bonus.c \
		ft_bresenham_bonus.c \
		ft_images_bonus.c \
		ft_mlx_close_bonus.c \
		raycast_start_bonus.c \
		redraw_bonus.c \
		setup_cubed_bonus.c \
		cub3D_texture_bonus.c \
		minimap_grid_bonus.c \
		cub3D_map_content_bonus.c \
		cub3D_map_valid_bonus.c \
		calculate_rays_bonus.c \
		handle_press_bonus.c \
		player_move_bonus.c \
		interact_bonus.c \
		cub3D_map_elems_bonus.c \
		init_scene_bonus.c \
		cub3D_map_bonus.c \
		cub3D_main_bonus.c \
		cub3D_parsing_utils_bonus.c \
		mouse_bonus.c \
		debug_bonus.c \

SRCFD = srcs/
SRCFD_BONUS = srcs/bonus/
OBJSFD = objs/
OBJSFD_BONUS = objs_bonus/
OBJ = $(ALL_SRCS:.c=.o)
OBJS = $(patsubst %, $(OBJSFD)%, $(OBJ))

ALL_BONUS_SRCS := $(filter-out valid_texture_utils.c debug.c cub3D_parsing_utils.c cub3D_main.c cub3D_map.c init_scene.c cub3D_map_elems.c raycast_start.c draw_raycast_view.c ft_images.c ft_mlx_close.c redraw.c setup_cubed.c cub3D_texture.c cub3D_map_content.c cub3D_map_valid.c calculate_rays.c handle_press.c player_move.c, $(ALL_SRCS))
ALL_BONUS_SRCS += $(BONUS)
OBJS_BONUS = $(patsubst %, $(OBJSFD_BONUS)%, $(ALL_BONUS_SRCS:.c=.o))

HEADER_PATH = -I ./includes
HEADER_PATH_BONUS = -I ./includes_bonus
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

LIBS = -Llibft -lft

.PHONY : all clean fclean re

all : $(NAME)

$(OBJSFD):
	@mkdir -p $(OBJSFD)

$(OBJSFD)%.o: $(RAYCAST_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(DRAWING_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(EXIT_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(EVENT_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(IMG_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(PLAYER_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(SETUP_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(TEXTURE_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(MAIN_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(OBJSFD)%.o: $(PARSE_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ $(HEADER_PATH)

$(NAME) : $(OBJSFD) $(OBJS) $(LIBFT)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $@..." $(NONE)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJS) $(LIBS) $(LINKS) -o $@
	@echo $(GREEN)"- Compiled $@ -"$(NONE)

bonus: $(NAME_BONUS)

$(OBJSFD_BONUS):
	@mkdir -p $(OBJSFD_BONUS)

$(OBJSFD_BONUS)%.o: $(RAYCAST_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(DRAWING_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(EXIT_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(EVENT_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(IMG_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(PLAYER_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(SETUP_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(TEXTURE_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(MAIN_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(PARSE_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@ 

$(OBJSFD_BONUS)%.o: $(BONUS_DIR)%.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@  $(HEADER_PATH_BONUS)

$(NAME_BONUS) : $(OBJSFD_BONUS) $(OBJS_BONUS) $(LIBFT)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $@..." $(NONE)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJS_BONUS) $(LIBS) $(LINKS) -o $@ $(HEADER_PATH_BONUS)
	@echo $(GREEN)"- Compiled $@ -"$(NONE)

$(LIBFT) :
	@echo $(CURSIVE)$(GRAY) "     - Compiling libft..." $(NONE)
	@make -C $(LIBFT_PATH)
	@echo $(GREEN)"- Compiled libft -"$(NONE)

clean :
	@rm -rf $(OBJSFD) $(OBJSFD_BONUS)
	@make fclean -C $(LIBFT_PATH)
	@echo $(CURSIVE)$(GRAY) "     - Deleted libft" $(NONE)
	@echo $(CURSIVE)$(GRAY) "     - Deleted object files" $(NONE)

fclean : clean
	@rm -f $(NAME)
	@echo $(CURSIVE)$(GRAY) "     - Deleted $(NAME)" $(NONE)
	@rm -f $(NAME_BONUS)
	@echo $(CURSIVE)$(GRAY) "     - Deleted $(NAME_BONUS)" $(NONE)
	@echo $(CURSIVE)$(YELLOW)"- fclean done "$(NONE)

re : fclean all

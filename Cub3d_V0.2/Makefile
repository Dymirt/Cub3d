# Program file name
NAME	= cub3D

# Compiler and compilation flags
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -g3

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
MLX_REPO 	= https://github.com/42Paris/minilibx-linux.git

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH = ./src/
SRC		= 	main.c \
			parsing/start_game.c \
			parsing/test_Data.c \
			parsing/test_TEX.c \
			parsing/test_ArgMap.c \
			parsing/test_MAP.c \
			moves/keypad.c \
			moves/dist_player.c \
			moves/maneuvers.c \
			img/camera.c \
			img/render.c \
			img/texture.c \
			img/image_utils.c \
			debug/StartData.c \
			debug/StartTex.c \
			debug/exit.c \
			debug/free_data.c \
			debug/debug.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./headers/ \
				-I ./libft/ \
				-I ./minilibx-linux/


# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/parsing
	@mkdir -p $(OBJ_PATH)/moves
	@mkdir -p $(OBJ_PATH)/img
	@mkdir -p $(OBJ_PATH)/debug

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	@echo -n "Building $(NAME)... "
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "done!"

# Libft rule
$(LIBFT):
	@$(MAKE) -s --no-print-directory -C $(LIBFT_PATH)

# MLX rule
$(MLX):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "Cloning minilibx-linux....."; \
		git clone $(MLX_REPO); \
	else \
		echo "Directory minilibx-linux already exsits, skip cloning"; \
	fi 
	@$(MAKE) -s --no-print-directory -C $(MLX_PATH)

# Clean up build files rule
clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -s --no-print-directory -C $(LIBFT_PATH) clean
	@$(MAKE) -s --no-print-directory -C $(MLX_PATH) clean
	@echo "Done!"

# Remove program executable
fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@$(MAKE) -s --no-print-directory -C $(LIBFT_PATH) fclean
	@echo "Done!"

# Clean + remove executable
re: fclean all
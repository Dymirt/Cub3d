# Program file name
NAME	= CUB3d

# Compiler and compilation flags
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -g3 #-fsanitize=address

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

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
			parsing/test_ARG.c \
			parsing/test_MAP.c \
			parsing/test_MAP2.c \
			parsing/test_COLOR.c \
			moves/keypad.c \
			moves/player_dir.c \
			moves/player_pos.c \
			moves/maneuvers.c \
			img/camera.c \
			img/render.c \
			img/texture.c \
			img/image_utils.c \
			img/minimap_image.c \
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

# Loading bar function
loading_bar:
	@printf "Loading: ["
	@for i in $$(seq 1 50); do \
		printf "\033[0;32m=\033[0m"; \
		sleep 0.05; \
	done; \
	printf "] Done!\n"

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
	@$(MAKE) loading_bar
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "done!"

# Libft rule
$(LIBFT):
	@$(MAKE) -s --no-print-directory -C $(LIBFT_PATH)

# MLX rule
$(MLX):
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

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
SRC		= $(shell find $(SRC_PATH) -type f -name '*.c')

# Objects
OBJ_PATH	= objects/
OBJS		=	$(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

# Includes
INC			=	-I ./headers/ \
				-I ./libft/ \
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Create objects directory
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
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
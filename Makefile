NAME        = cub3D
# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_DIR = mlx/linux
else
    MLX_DIR = mlx/macOS
endif

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -I./includes -I./libft -I./get_next_line -I$(MLX_DIR)
ifeq ($(UNAME_S),Linux)
    LIBS = -L./libft -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else
    LIBS = -L./libft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes
LIBFT_DIR   = libft
GNL_DIR     = get_next_line

# Source files
SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/init_utils.c \
			  $(SRC_DIR)/free_utils.c \
              $(SRC_DIR)/parsing/parse_file.c \
              $(SRC_DIR)/parsing/parse_texture.c \
              $(SRC_DIR)/parsing/parse_color.c \
              $(SRC_DIR)/parsing/parse_color_utils.c \
              $(SRC_DIR)/parsing/parse_map.c \
              $(SRC_DIR)/parsing/parse_map_utils.c \
              $(SRC_DIR)/validation/validate.c \
              $(SRC_DIR)/validation/validate_chars.c \
              $(SRC_DIR)/utils/utils.c \
              $(SRC_DIR)/utils/string_utils.c \
              $(SRC_DIR)/textures/load_textures.c \
              $(SRC_DIR)/render/init_game.c \
              $(SRC_DIR)/render/pixel.c \
              $(SRC_DIR)/render/draw.c \
              $(SRC_DIR)/render/raycasting.c \
              $(SRC_DIR)/render/render_wall.c \
              $(SRC_DIR)/render/render.c \
              $(SRC_DIR)/events/events.c \
              $(SRC_DIR)/events/movement.c \
              $(SRC_DIR)/events/game_loop.c 
			  
# GNL files
GNL_SRCS    = $(GNL_DIR)/get_next_line.c \
              $(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
GNL_OBJS    = $(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJ_DIR)/gnl/%.o)

ALL_OBJS    = $(OBJS) $(GNL_OBJS)

# Libft
LIBFT       = $(LIBFT_DIR)/libft.a

# MLX
MLX         = $(MLX_DIR)/libmlx.a

# Colors for pretty output
GREEN       = \033[0;32m
RED         = \033[0;31m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
RESET       = \033[0m

# Progress
TOTAL       = $(words $(SRCS) $(GNL_SRCS))
CURRENT     = 0

# Rules
all: header $(LIBFT) $(MLX) $(NAME) footer

header:
	@echo "$(CYAN)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║                                        ║"
	@echo "║           Building Cub3D               ║"
	@echo "║                                        ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"

footer:
	@echo "$(GREEN)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║                                        ║"
	@echo "║        ✓ Build Complete!               ║"
	@echo "║                                        ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"

$(NAME): $(ALL_OBJS)
	@echo "$(YELLOW)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(ALL_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

$(LIBFT):
	@echo "$(MAGENTA)📚 Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft ready!$(RESET)"

$(MLX):
	@echo "$(MAGENTA)📚 Building mlx...$(RESET)"
	@make -C $(MLX_DIR) --no-print-directory 2>/dev/null
	@echo "$(GREEN)✓ mlx ready!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	@printf "$(BLUE)[%3d/%3d] $(CYAN)Compiling $(RESET)%-50s" $(CURRENT) $(TOTAL) "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)✓$(RESET)"

$(OBJ_DIR)/gnl/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/gnl
	@$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	@printf "$(BLUE)[%3d/%3d] $(CYAN)Compiling $(RESET)%-50s" $(CURRENT) $(TOTAL) "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)✓$(RESET)"

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

# Test with a valid map
test: $(NAME)
	@echo "$(YELLOW)🧪 Running test...$(RESET)"
	@./$(NAME) maps/test.cub

# Memory leak check with valgrind
leaks: $(NAME)
	@echo "$(YELLOW)🔍 Checking for memory leaks...$(RESET)"
	@valgrind --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          --verbose \
	          --log-file=valgrind-out.txt \
	          ./$(NAME) maps/test.cub
	@echo "$(GREEN)✓ Check complete! See valgrind-out.txt$(RESET)"

# Debug build with sanitizers
debug: CFLAGS += -g3 -fsanitize=address -fsanitize=undefined
debug: re
	@echo "$(MAGENTA)🐛 Debug build complete with sanitizers!$(RESET)"

# Show compilation database (useful for LSP)
bear: fclean
	@bear -- make

.PHONY: all clean fclean re test leaks debug bear header footer

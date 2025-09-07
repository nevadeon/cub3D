NAME := cub3D

CC := cc
CFLAGS = -Wall -Wextra -I$(INC_PATH) -g -Iminilibx-linux
CFLAGS += $(foreach dir, $(shell find $(INC_PATH) -type d), -I$(PATH))
LDFLAGS = -lXext -lX11 -lm -lz -I.
GDB_FLAGS := --quiet --args

MLX_PATH := minilibx-linux
INC_PATH := include
SRC_PATH := src
OBJ_PATH := obj

SRC := $(shell find $(SRC_PATH) -type f -name "*.c")
OBJ := $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

# ============================================================================ #
#        Main rules                                                            #
# ============================================================================ #

all: $(NAME)

$(MLX_PATH)/libmlx.a:
	$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJ) $(MLX_PATH)/libmlx.a
	@$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@./update_progress_bar.sh "Compiling $(NAME):"

re: fclean all

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

# ============================================================================ #
#        Test rules                                                            #
# ============================================================================ #

valgrind: all
	valgrind ./$(NAME)

gdb: all
	gdb $(GDB_FLAGS) ./$(NAME)

test-invalid-maps: all
	@for f in maps/invalid*; do \
		echo $$f...; \
		./$(NAME) "$$f" && echo "UNEXPECTED PASS"; \
		echo exit code $$?; echo;\
	done;

test: CFLAGS+=-fsanitize=address
test: LDFLAGS+=-fsanitize=address
test: re

.PHONY: all re clean fclean valgrind gdb test test-invalid-maps

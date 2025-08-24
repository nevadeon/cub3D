NAME := cub3D

# Compiler, flags and args
CC := cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -g
CFLAGS += $(foreach dir, $(shell find $(INC_DIR) -type d), -I$(dir))
LDFLAGS =
GDB_FLAGS := --quiet --args

# Directories
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj

# Sources and objects
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ============================================================================ #
#        Main rules                                                            #
# ============================================================================ #
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@./update_progress_bar.sh "Compiling $(NAME):"

re: fclean all

clean:
	@rm -rf $(OBJ_DIR)

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
	@set -e; for f in maps/invalid*; do \
		[ -e "$$f" ] || continue; \
		printf "%s...\n" "$$f"; \
		./$(NAME) "$$f" && echo "UNEXPECTED PASS"; echo;\
	done;

.PHONY: all re clean fclean valgrind gdb test-invalid-maps
